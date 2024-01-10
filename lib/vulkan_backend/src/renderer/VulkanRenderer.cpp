#if USE_VULKAN

#include "renderer/VulkanRenderer.hpp"
#include <stdexcept>
#include "CharUtil.hpp"
#include <set>
#include <algorithm>
#include "VulkanUtil.hpp"
#include "Mat4x4.hpp"

namespace bns
{
	VulkanRenderer::VulkanRenderer(WindowManager *windowManager)
		: m_windowManager(windowManager), m_instance(nullptr)
	{
	}

	bool VulkanRenderer::IsLayerSupported(const std::string &layer)
	{
		u32 layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

		std::vector<VkLayerProperties> availableLayers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

		for (size_t i = 0; i < availableLayers.size(); i++)
		{
			if (std::string(availableLayers[i].layerName) == layer)
			{
				return true;
			}
		}

		return false;
	}

	VKAPI_ATTR VkBool32 VKAPI_CALL VulkanRenderer::DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
																 VkDebugUtilsMessageTypeFlagsEXT messageType,
																 const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
																 void *pUserData)
	{
		LOG("VulkanRenderer::DebugCallback: %s\n", pCallbackData->pMessage);

		return VK_FALSE; // return true if the call should be aborted. This is almost never the case. We just want to log the error.
	}

	void VulkanRenderer::RecordCommandBuffer(VkCommandBuffer commandBuffer, u32 imageIndex)
	{
	}

	void VulkanRenderer::Initialize(const std::vector<std::string> &requiredExtensions)
	{
		// CREATE INSTANCE
		// Create app info. This is optional but can be useful for drivers to optimize our specific application.
		VkApplicationInfo appInfo = VulkanUtil::ApplicationInfo.Create();

		// Of we are in debug mode, we want to have debug utils extension enabled.
		std::vector<std::string> copyRequiredExtensions = requiredExtensions;
#if DEBUG
		copyRequiredExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME); // this extension is used for debug purposes. We can use it to log errors and warnings.
#endif

		m_instance = VulkanUtil::Instance.Create(appInfo, copyRequiredExtensions, m_validationLayers);

		VulkanUtil::Instance.PrintAvailableExtensionsAndLayers();

		// PHYSICAL DEVICE
		m_physicalDevice = VulkanUtil::PhysicalDevice.PickPhysicalDevice(m_instance, m_deviceExtensions);

		// SURFACE
		m_surface = m_windowManager->CreateVulkanSurface(m_instance);

		// QUEUE FAMILY INDICES
		VulkanUtil::PhysicalDevice.GetQueueFamilyIndices(m_physicalDevice, m_surface, &m_graphicsQueueFamilyIndex, &m_presentQueueFamilyIndex);

#if DEBUG
		// DEBUG MESSENGER
		m_debugMessenger = VulkanUtil::DebugUtilsMessengerEXT.Create(m_instance, DebugCallback);
#endif
		// LOGICAL DEVICE
		std::vector<f32> queuePriorities = {1.0f};
		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos =
			{
				VulkanUtil::DeviceQueueCreateInfo.Create(m_graphicsQueueFamilyIndex, queuePriorities),
				VulkanUtil::DeviceQueueCreateInfo.Create(m_presentQueueFamilyIndex, queuePriorities)};

		// If the graphics and present queue are the same, we only need one queue.
		if (m_graphicsQueueFamilyIndex == m_presentQueueFamilyIndex)
		{
			queueCreateInfos = {queueCreateInfos[0]};
		}

		VkPhysicalDeviceFeatures deviceFeatures;
		vkGetPhysicalDeviceFeatures(m_physicalDevice, &deviceFeatures);
		m_device = VulkanUtil::Device.Create(m_physicalDevice, queueCreateInfos, deviceFeatures, m_deviceExtensions, m_validationLayers);

		// QUEUES
		vkGetDeviceQueue(m_device, m_graphicsQueueFamilyIndex, 0, &m_graphicsQueue);
		vkGetDeviceQueue(m_device, m_presentQueueFamilyIndex, 0, &m_presentQueue);

		// SWAP CHAIN KHR
		Vec2i windowSize = m_windowManager->GetWindowSize();
		m_swapChain = VulkanUtil::SwapChainKHR.Create(m_physicalDevice,
													  m_device,
													  m_surface,
													  windowSize.X, windowSize.Y,
													  &m_swapChainImages,
													  &m_swapChainImageFormat,
													  &m_swapChainExtent);

		// SWAP CHAIN IMAGE VIEWS
		for (VkImage &image : m_swapChainImages)
		{
			m_swapChainImageViews.push_back(VulkanUtil::ImageView.Create(m_device, image, m_swapChainImageFormat));
		}

		// RENDER PASS
		// Create the color attachment
		VkAttachmentDescription colorAttachment = VulkanUtil::AttachmentDescription.CreateColorAttachment(m_swapChainImageFormat);

		// Create the color attachment for location 0
		VkAttachmentReference colorAttachmentRef = VulkanUtil::AttachmentReference.CreateColorAttachmentRef(0);

		// Create the subpass description
		std::vector<VkAttachmentReference> colorAttachmentRefs = {colorAttachmentRef};
		VkSubpassDescription subpass = VulkanUtil::SubpassDescription.Create(colorAttachmentRefs);

		// Create the render pass
		std::vector<VkAttachmentDescription> attachments = {colorAttachment};
		std::vector<VkSubpassDescription> subpasses = {subpass};
		m_renderPass = VulkanUtil::RenderPass.Create(m_device, attachments, subpasses);

		LOG("VulkanRenderer::SetupRenderPass: Render pass created.\n");

		// TEST PIPELINE
		VkShaderModule vertShaderModule = VulkanUtil::ShaderModule.CreateFromSpirVFilepath(m_device, "shaders/vulkan/test/triangle_vs.spv");
		VkShaderModule fragShaderModule = VulkanUtil::ShaderModule.CreateFromSpirVFilepath(m_device, "shaders/vulkan/test/triangle_fs.spv");

        std::vector<VkDescriptorSetLayout> descriptorSetLayouts = {};
        std::vector<VkPushConstantRange> pushConstantRanges = {
			VulkanUtil::PushConstantRange.Create(VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(f32) * 16)
		};
       	m_pipelineLayout = VulkanUtil::PipelineLayout.Create(m_device, descriptorSetLayouts, pushConstantRanges);

		m_pipeline = VulkanUtil::Pipeline.Create(m_device, vertShaderModule, fragShaderModule, m_renderPass, m_pipelineLayout, m_swapChainExtent);

		// FRAMEBUFFERS - setup framebuffers
		m_framebuffers = VulkanUtil::Framebuffer.Create(m_device, m_renderPass, m_swapChainImageViews, m_swapChainExtent);

		// COMMAND POOL - setup command pool
		m_commandPool = VulkanUtil::CommandPool.Create(m_device, m_graphicsQueueFamilyIndex);

		// COMMAND BUFFER - setup command buffer
		m_commandBuffer = VulkanUtil::CommandBuffer.Create(m_device, m_commandPool, VK_COMMAND_BUFFER_LEVEL_PRIMARY);

		// SYNCHRONIZATION OBJECTS - semaphores and fences to synchronize rendering
		m_imageAvailableSemaphore = VulkanUtil::Semaphore.Create(m_device);
		m_renderFinishedSemaphore = VulkanUtil::Semaphore.Create(m_device);
		// the fence is used to synchronize CPU and GPU. We want to wait for the GPU to finish rendering before we start rendering again.
		// create the fence in the signaled state. This means that the GPU is allowed to start rendering.
		m_inFlightFence = VulkanUtil::Fence.Create(m_device, VK_FENCE_CREATE_SIGNALED_BIT);

		return;
	}

	void VulkanRenderer::BeginDraw()
	{
		// WAIT FOR FENCE - wait for the fences. Means that CPU will wait for the GPU to finish rendering, and therefore be synchronized.
		if (vkWaitForFences(m_device, 1, &m_inFlightFence, VK_TRUE, UINT64_MAX) != VK_SUCCESS)
		{
			std::string msg = "VulkanRenderer::BeginDraw: Failed to wait for fence!";
			LOG(msg.c_str());
			BREAKPOINT();
			throw std::runtime_error(msg);
		}

		// RESET FENCE - reset the fence to be unsignaled. This means that the GPU is now allowed to start rendering.
		if (vkResetFences(m_device, 1, &m_inFlightFence) != VK_SUCCESS)
		{
			std::string msg = "VulkanRenderer::BeginDraw: Failed to reset fence!";
			LOG(msg.c_str());
			BREAKPOINT();
			throw std::runtime_error(msg);
		}

		// ACQUIRE IMAGE INDEX - here we wait for the image to be available.
		if (vkAcquireNextImageKHR(m_device, m_swapChain, UINT64_MAX, m_imageAvailableSemaphore, VK_NULL_HANDLE, &m_currentFrameIndex) != VK_SUCCESS)
		{
			std::string msg = "VulkanRenderer::BeginDraw: Failed to acquire swap chain image!";
			LOG(msg.c_str());
			BREAKPOINT();
			throw std::runtime_error(msg);
		}

		// RESET COMMAND BUFFER
		if (vkResetCommandBuffer(m_commandBuffer, 0) != VK_SUCCESS)
		{
			std::string msg = "VulkanRenderer::BeginDraw: Failed to reset command buffer!";
			LOG(msg.c_str());
			BREAKPOINT();
			throw std::runtime_error(msg);
		}

		// RECORD COMMAND BUFFER
		VkCommandBufferBeginInfo beginInfo = VulkanUtil::CommandBufferBeginInfo.Create();
		if (vkBeginCommandBuffer(m_commandBuffer, &beginInfo) != VK_SUCCESS)
		{
			std::string msg = "VulkanRenderer::RecordCommandBuffer: Failed to begin recording command buffer!";
			LOG(msg.c_str());
			BREAKPOINT();
			throw std::runtime_error(msg);
		}

		// CLEAR COLOR
		VkClearValue clearColor = {ClearColor.R, ClearColor.G, ClearColor.B, ClearColor.A};

		// BEGIN RENDER PASS
		VkRenderPassBeginInfo renderPassInfo = VulkanUtil::RenderPassBeginInfo.Create(m_renderPass,
																					  m_framebuffers[m_currentFrameIndex],
																					  m_swapChainExtent,
																					  clearColor);

		// Viewport
		VkViewport viewport = VulkanUtil::Viewport.Create(m_swapChainExtent);
		vkCmdSetViewport(m_commandBuffer, 0, 1, &viewport);

		// Scissor
		VkRect2D scissor{};
		scissor.offset = {0, 0};
		scissor.extent = m_swapChainExtent;
		vkCmdSetScissor(m_commandBuffer, 0, 1, &scissor);

		// BEGIN RENDER PASS
		vkCmdBeginRenderPass(m_commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

		// DRAW
		vkCmdBindPipeline(m_commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipeline);
		
		for(u32 i = 0; i < 3; i++)
		{
			Mat4x4f model = Mat4x4f::TranslationMatrix(i * 0.5f, 0.0f, 0.0f);
			vkCmdPushConstants(m_commandBuffer, m_pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(f32) * 16, &model);
			vkCmdDraw(m_commandBuffer, 3, 1, 0, 0);
		}
	}

	void VulkanRenderer::EndDraw()
	{
		// end render pass
		vkCmdEndRenderPass(m_commandBuffer);

		// end recording
		if (vkEndCommandBuffer(m_commandBuffer) != VK_SUCCESS)
		{
			std::string msg = "VulkanRenderer::RecordCommandBuffer: Failed to record command buffer!";
			LOG(msg.c_str());
			BREAKPOINT();
			throw std::runtime_error(msg);
		}

		VkPipelineStageFlags waitStage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		VkSubmitInfo submitInfo = VulkanUtil::SubmitInfo.CreateGraphicsSubmitInfo(m_imageAvailableSemaphore,
																				  waitStage,
																				  m_commandBuffer,
																				  m_renderFinishedSemaphore);

		// submit command buffer
		if (vkQueueSubmit(m_graphicsQueue, 1, &submitInfo, m_inFlightFence) != VK_SUCCESS)
		{
			std::string msg = "VuekanRenderer::EndDraw: Failed to submit draw command buffer!";
			LOG("%s", msg.c_str());
			BREAKPOINT();
			throw std::runtime_error(msg);
		}

		// PRESENT
		VkPresentInfoKHR presentInfo{};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

		// Wait on these semaphores before presenting. This waits until the render is finished.
		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = &m_renderFinishedSemaphore;

		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = &m_swapChain;
		presentInfo.pImageIndices = &m_currentFrameIndex;

		presentInfo.pResults = nullptr; // Optional

		// PRESENT
		vkQueuePresentKHR(m_presentQueue, &presentInfo);
	}

	void VulkanRenderer::Destroy()
	{
		// SYNCHRONIZATION OBJECTS - destroy semaphores and fences
		VulkanUtil::Semaphore.Destroy(m_device, m_imageAvailableSemaphore);
		VulkanUtil::Semaphore.Destroy(m_device, m_renderFinishedSemaphore);
		VulkanUtil::Fence.Destroy(m_device, m_inFlightFence);

		VulkanUtil::CommandPool.Destroy(m_device, m_commandPool);
		for (auto framebuffer : m_framebuffers)
		{
			VulkanUtil::Framebuffer.Destroy(m_device, framebuffer);
		}
		for (size_t i = 0; i < m_swapChainImageViews.size(); i++)
		{
			vkDestroyImageView(m_device, m_swapChainImageViews[i], nullptr);
		}
		VulkanUtil::RenderPass.Destroy(m_device, m_renderPass);
		vkDestroySwapchainKHR(m_device, m_swapChain, nullptr);
		vkDestroySurfaceKHR(m_instance, m_surface, nullptr);
		if (m_debugMessenger != nullptr)
		{
			// load function and call it.
			auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(m_instance, "vkDestroyDebugUtilsMessengerEXT");
			func(m_instance, m_debugMessenger, nullptr);
		}
		vkDestroyDevice(m_device, nullptr);
		vkDestroyInstance(m_instance, nullptr);
	}

	void *VulkanRenderer::GetSwapChainTexture()
	{
		return nullptr;
	}

	void VulkanRenderer::Resize()
	{
	}
}

#endif