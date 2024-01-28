#if USE_VULKAN

#include "renderer/VulkanRenderer.hpp"
#include <stdexcept>
#include "CharUtil.hpp"
#include <set>
#include <algorithm>
#include "VulkanUtil.hpp"
#include "Mat4x4.hpp"
#include "ImageLoader.hpp"
#include "sprite/VulkanUnlitSpritePipeline.hpp"

namespace bns
{
	VulkanRenderer::VulkanRenderer(WindowManager *windowManager)
		: m_windowManager(windowManager), m_instance(nullptr), m_swapchainOutOfDateFlag(false)
	{
		m_windowManager->RegisterToWindowResize([this](Vec2i size)
												{ m_swapchainOutOfDateFlag = true; });
	}

	void VulkanRenderer::CheckValidationLayerSupport()
	{
		// Get count of available layers
		u32 propertyCount = 0;
		vkEnumerateInstanceLayerProperties(&propertyCount, nullptr);

		// Get available layers
		std::vector<VkLayerProperties> availableLayers(propertyCount);
		vkEnumerateInstanceLayerProperties(&propertyCount, availableLayers.data());

		// Check if all layers are supported
		// Go through each required layer and compare it to the available layers
		for (const std::string &layer : m_validationLayers)
		{
			bool layerFound = false;

			// Check against availalbe layers
			for (const VkLayerProperties &availableLayer : availableLayers)
			{
				if (strcmp(layer.c_str(), availableLayer.layerName) == 0)
				{
					layerFound = true;
					break;
				}
			}

			// If we didn't find the layer, throw an error
			if (!layerFound)
			{
				std::string msg = "VulkanRenderer::CheckValidationLayerSupport: Validation layer " + layer + " not is not supported!";
				LOG(msg);
				BREAKPOINT();
				throw std::runtime_error(msg);
			}
		}
	}

	void VulkanRenderer::CreateInstance(const std::vector<std::string> &requiredExtensions)
	{
		// If we are in debug mode, we want to have debug utils extension enabled.
		std::vector<std::string> copyRequiredExtensions = m_additionalExtensions;
		copyRequiredExtensions.insert(copyRequiredExtensions.end(), requiredExtensions.begin(), requiredExtensions.end());
		m_instance = VulkanUtil::Instance.Create(copyRequiredExtensions, m_validationLayers);
	}

	VKAPI_ATTR VkBool32 VKAPI_CALL VulkanRenderer::DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
																 VkDebugUtilsMessageTypeFlagsEXT messageType,
																 const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
																 void *pUserData)
	{
		std::string msg = "VulkanRenderer::DebugCallback: " + std::string(pCallbackData->pMessage);
		LOG(msg);

		return VK_FALSE; // return true if the call should be aborted. This is almost never the case. We just want to log the error.
	}

	void VulkanRenderer::Initialize(const std::vector<std::string> &requiredExtensions)
	{
		CheckValidationLayerSupport();
		CreateInstance(requiredExtensions);

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

		m_device = VulkanUtil::Device.Create(m_physicalDevice, queueCreateInfos, m_deviceExtensions, m_validationLayers);

		// QUEUES
		vkGetDeviceQueue(m_device, m_graphicsQueueFamilyIndex, 0, &m_graphicsQueue);
		vkGetDeviceQueue(m_device, m_presentQueueFamilyIndex, 0, &m_presentQueue);

		// SWAP CHAIN KHR
		CreateSwapchain();

		// SWAP CHAIN IMAGE VIEWS
		CreateSwapchainImageViews();

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

		// COMMAND POOL - setup command pool
		m_commandPool = VulkanUtil::CommandPool.Create(m_device, m_graphicsQueueFamilyIndex);

		LOG("VulkanRenderer::SetupRenderPass: Render pass created.\n");

		// FRAMEBUFFERS - setup framebuffers
		CreateFramebuffers();

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
			LOG(msg);
			BREAKPOINT();
			throw std::runtime_error(msg);
		}

		// ACQUIRE IMAGE INDEX - here we wait for the image to be available.
		VkResult result = vkAcquireNextImageKHR(m_device, m_swapChain, 1000 * 1000, m_imageAvailableSemaphore, VK_NULL_HANDLE, &m_currentFrameIndex);
		if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || m_swapchainOutOfDateFlag)
		{
			RecreateSwapchain();
			LOG("VulkanRenderer::BeginDraw: Swapchain out of date. Recreating swapchain.\n");
		}
		else if (result != VK_SUCCESS)
		{
			std::string msg = "VulkanRenderer::BeginDraw: Failed to acquire swap chain image!";
			LOG(msg);
			BREAKPOINT();
			throw std::runtime_error(msg);
		}

		// RESET FENCE - reset the fence to be unsignaled. This means that the GPU is now allowed to start rendering.
		if (vkResetFences(m_device, 1, &m_inFlightFence) != VK_SUCCESS)
		{
			std::string msg = "VulkanRenderer::BeginDraw: Failed to reset fence!";
			LOG(msg);
			BREAKPOINT();
			throw std::runtime_error(msg);
		}

		// RESET COMMAND BUFFER
		if (vkResetCommandBuffer(m_commandBuffer, 0) != VK_SUCCESS)
		{
			std::string msg = "VulkanRenderer::BeginDraw: Failed to reset command buffer!";
			LOG(msg);
			BREAKPOINT();
			throw std::runtime_error(msg);
		}

		// RECORD COMMAND BUFFER
		VkCommandBufferBeginInfo beginInfo = VulkanUtil::CommandBufferBeginInfo.Create();
		if (vkBeginCommandBuffer(m_commandBuffer, &beginInfo) != VK_SUCCESS)
		{
			std::string msg = "VulkanRenderer::RecordCommandBuffer: Failed to begin recording command buffer!";
			LOG(msg);
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

		// VIEWPORT - note that view y is flipped.
		// This is because by default vulkan y is positive down, but we want positive up like
		// in Metal, WebGPu, OpenGL, and DirectX.
		// Space now is x: [-1, 1], y: [-1, 1], z: [0, 1]
		VkViewport viewport;
		viewport.x = 0.0f;
		viewport.y = m_swapChainExtent.height;
		viewport.width = m_swapChainExtent.width;
		viewport.height = -static_cast<f32>(m_swapChainExtent.height);
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;
		vkCmdSetViewport(m_commandBuffer, 0, 1, &viewport);

		// Scissor
		VkRect2D scissor{};
		scissor.offset = {0, 0};
		scissor.extent = m_swapChainExtent;
		vkCmdSetScissor(m_commandBuffer, 0, 1, &scissor);

		// BEGIN RENDER PASS
		vkCmdBeginRenderPass(m_commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
	}

	void VulkanRenderer::EndDraw()
	{
		// end render pass
		vkCmdEndRenderPass(m_commandBuffer);

		// end recording
		if (vkEndCommandBuffer(m_commandBuffer) != VK_SUCCESS)
		{
			std::string msg = "VulkanRenderer::RecordCommandBuffer: Failed to record command buffer!";
			LOG(msg);
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
			LOG( msg);
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
		VkResult result = vkQueuePresentKHR(m_presentQueue, &presentInfo);
		if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR)
		{
			RecreateSwapchain();
			LOG("VulkanRenderer::EndDraw: Swapchain out of date. Recreating swapchain.");
		}
		else if (result != VK_SUCCESS)
		{
			std::string msg = "VulkanRenderer::EndDraw: Failed to present swap chain image!";
			LOG(msg);
			BREAKPOINT();
			throw std::runtime_error(msg);
		}
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

	void VulkanRenderer::CreateSwapchain()
	{
		Vec2i windowSize = m_windowManager->GetWindowSize();
		m_bufferSize = windowSize;
		m_swapChain = VulkanUtil::SwapChainKHR.Create(m_physicalDevice,
													  m_device,
													  m_surface,
													  windowSize.X, windowSize.Y,
													  &m_swapChainImages,
													  &m_swapChainImageFormat,
													  &m_swapChainExtent);
		m_currentFrameIndex = 0;
	}

	void VulkanRenderer::CreateSwapchainImageViews()
	{
		for (VkImage &image : m_swapChainImages)
		{
			m_swapChainImageViews.push_back(VulkanUtil::ImageView.Create(m_device, image, m_swapChainImageFormat));
		}
	}

	void VulkanRenderer::CreateFramebuffers()
	{
		m_framebuffers = VulkanUtil::Framebuffer.Create(m_device, m_renderPass, m_swapChainImageViews, m_swapChainExtent);
	}

	void VulkanRenderer::RecreateSwapchain()
	{
		m_swapchainOutOfDateFlag = false;

		// DESTROY OLD RESOURCES - destroy old framebuffers, imageview, swapchain, images
		for (VkFramebuffer &framebuffer : m_framebuffers)
		{
			vkDestroyFramebuffer(m_device, framebuffer, nullptr);
		}
		m_framebuffers.clear();

		for (VkImageView &imageView : m_swapChainImageViews)
		{
			vkDestroyImageView(m_device, imageView, nullptr);
		}
		m_swapChainImageViews.clear();

		// images just need to be cleared
		m_swapChainImages.clear();

		vkDestroySwapchainKHR(m_device, m_swapChain, nullptr);

		vkDeviceWaitIdle(m_device);

		CreateSwapchain();
		CreateSwapchainImageViews();
		CreateFramebuffers();
	}
}

#endif