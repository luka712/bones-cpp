#if USE_VULKAN

#include "renderer/VulkanRenderer.hpp"
#include <stdexcept>
#include "CharUtil.hpp"
#include <set>
#include <algorithm>
#include "VulkanUtil.hpp"

namespace bns
{
	VulkanRenderer::VulkanRenderer(WindowManager *windowManager)
		: m_windowManager(windowManager), m_instance(nullptr)
	{
	}

	void VulkanRenderer::SetupInstance(const std::vector<std::string> &requiredWindowExtensions)
	{
		// create app info
		VkApplicationInfo appInfo{};
		appInfo.pNext = nullptr;
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Bones Framework";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "Bones Framework";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);

		// create instance info
		VkInstanceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

		// SETUP EXTENSIONS
		std::vector<std::string> requiredExtensions = requiredWindowExtensions;
#if DEBUG
		requiredExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME); // this extension is used for debug purposes. We can use it to log errors and warnings.
#endif
		createInfo.enabledExtensionCount = static_cast<u32>(requiredExtensions.size());
		char **pRequiredExtensions = CharUtil::CreateCopy(requiredExtensions);
		createInfo.ppEnabledExtensionNames = pRequiredExtensions;

		// SETUP VALIDATION LAYER
#if DEBUG
		for (const char *layer : m_validationLayers)
		{
			if (!IsLayerSupported(layer))
			{
				std::string msg = "SDLWindowManager::SetupInstance: Validation layer not supported.";
				LOG(msg.c_str());
				BREAKPOINT();
				throw std::runtime_error(msg.c_str());
			}

			LOG("SDLWindowManager::SetupInstance: Validation layer supported: %s\n", layer);
		}
		createInfo.enabledLayerCount = static_cast<u32>(m_validationLayers.size());
		createInfo.ppEnabledLayerNames = m_validationLayers.data();
#else
		createInfo.enabledLayerCount = 0;
#endif
		// CREATE INSTANCE
		// Create instance and check result.
		VkResult result = vkCreateInstance(&createInfo, nullptr, &m_instance);
		if (result != VK_SUCCESS)
		{
			std::string msg = "SDLWindowManager::SetupInstance: Failed to create Vulkan instance.";
			LOG(msg.c_str());
			BREAKPOINT();
			throw std::runtime_error(msg.c_str());
		}

		// CHECK EXTENSIONS
		// if debug just print available extensions
#if DEBUG
		// just check extensions
		u32 extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

		std::vector<VkExtensionProperties> extensions(extensionCount);

		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

		for (const auto &extension : extensions)
		{
			LOG("VulkanRenderer::SetupInstance: Available Vulkan Extension: %s\n", extension.extensionName);
		}
#endif

		// release memory
		for (size_t i = 0; i < requiredWindowExtensions.size(); i++)
		{
			delete pRequiredExtensions[i];
		}
		delete[] pRequiredExtensions;
	}

	void VulkanRenderer::SetupSurface()
	{
		// create surface
		m_surface = m_windowManager->CreateVulkanSurface(m_instance);
		if (m_surface == VK_NULL_HANDLE || m_surface == nullptr)
		{
			std::string msg = "VulkanRenderer::SetupSurface: Failed to create Vulkan surface!";
			LOG(msg.c_str());
			BREAKPOINT();
			throw std::runtime_error(msg);
		}
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

	void VulkanRenderer::SetupDebugUtilsMessengerEXT()
	{
		VkDebugUtilsMessengerCreateInfoEXT createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		createInfo.pfnUserCallback = DebugCallback;
		createInfo.pUserData = nullptr; // Optional

		// load function
		auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(m_instance, "vkCreateDebugUtilsMessengerEXT");

		// function not found
		if (func == nullptr)
		{
			std::string msg = "VulkanRenderer::SetupDebugUtilsMessengerEXT: Failed to setup debug messenger! Function not found!";
			LOG(msg.c_str());
			BREAKPOINT();
			throw std::runtime_error(msg);
		}

		// if we have function, call it and check result.
		if (func(m_instance, &createInfo, nullptr, &m_debugMessenger) != VK_SUCCESS)
		{
			std::string msg = "VulkanRenderer::SetupDebugUtilsMessengerEXT: Failed to setup debug messenger! Function returned error!";
			LOG(msg.c_str());
			BREAKPOINT();
			throw std::runtime_error(msg);
		}

		LOG("VulkanRenderer::SetupDebugUtilsMessengerEXT: Debug messenger setup successfully!\n");
	}

	void VulkanRenderer::SetupPhysicalDevice()
	{

		m_physicalDevice = VK_NULL_HANDLE; // set to null handle

		// find count of devices
		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(m_instance, &deviceCount, nullptr);

		if (deviceCount == 0)
		{
			std::string msg = "VulkanRenderer::Initialize: Failed to find GPUs with Vulkan support!";
			LOG(msg.c_str());
			BREAKPOINT();
			throw std::runtime_error(msg);
		}

		LOG("VulkanRenderer::Initialize: Found %d devices.\n", deviceCount);

		// Get devices and use suitable device
		m_availableDevices = std::vector<VkPhysicalDevice>(deviceCount);
		vkEnumeratePhysicalDevices(m_instance, &deviceCount, m_availableDevices.data());

		for (const VkPhysicalDevice &device : m_availableDevices)
		{
			VkPhysicalDeviceProperties deviceProperties;
			vkGetPhysicalDeviceProperties(device, &deviceProperties);

			bool swapChainAdequate = false;
			if (CheckDeviceExtensionSupport(device))
			{
				VulkanSwapChainSupportDetails swapChainSupport = QuerySwapChainSupport(device);
				swapChainAdequate = swapChainSupport.IsValid();
			}

			// select first discrete gpu
			if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU // check if it is discrete gpu
				&& FindValidQueueFamilyIndices(device, &m_queueFamilyIndices)		// check if all indices are found. m_queueFamilyIndices is set here as well as out parameter.
				&& CheckDeviceExtensionSupport(device)								// check if device supports required extensions
				&& swapChainAdequate)												// check if swap chain is adequate
			{
				m_physicalDevice = device;
				break;
			}
		}

		// if we didn't find discrete gpu, just select first one.
		// we need to setup indices for it as well.
		if (m_physicalDevice == VK_NULL_HANDLE)
		{
			m_physicalDevice = m_availableDevices[0];
			FindValidQueueFamilyIndices(m_physicalDevice, &m_queueFamilyIndices);
		}
	}

	bool VulkanRenderer::FindValidQueueFamilyIndices(VkPhysicalDevice physicalDevice, VulkanQueueFamilyIndices *outQueueFamilyIndices)
	{
		u32 queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);

		LOG("VulkanRenderer::SetupQueueFamilyIndices: Found %d queue families.\n", queueFamilyCount);

		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());

		i32 i = 0;
		for (const VkQueueFamilyProperties &queueFamily : queueFamilies)
		{
			if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				outQueueFamilyIndices->GraphicsFamily = i;
				LOG("VulkanRenderer::SetupQueueFamilyIndices: Found graphics queue family at index %d.\n", i);
			}

			VkBool32 presentSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, m_surface, &presentSupport);
			if (presentSupport)
			{
				outQueueFamilyIndices->PresentFamily = i;
				LOG("VulkanRenderer::SetupQueueFamilyIndices: Found present queue family at index %d.\n", i);
			}

			if (outQueueFamilyIndices->IsValid())
			{
				break;
			}

			i++;
		}

		return outQueueFamilyIndices->IsValid();
	}

	void VulkanRenderer::SetupLogicalDevice()
	{
		// create queue create info
		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
		std::set<uint32_t> uniqueQueueFamilies = {
			m_queueFamilyIndices.GraphicsFamily.value(),
			m_queueFamilyIndices.PresentFamily.value()};

		f32 queuePriority = 1.0f;
		for (u32 queueFamily : uniqueQueueFamilies)
		{
			VkDeviceQueueCreateInfo queueCreateInfo{};
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueFamilyIndex = queueFamily;
			queueCreateInfo.queueCount = 1; // we only need one queue
			queueCreateInfo.pQueuePriorities = &queuePriority;
			queueCreateInfos.push_back(queueCreateInfo);
		}

		VkPhysicalDeviceFeatures deviceFeatures{}; // empty for now

		// create device create info
		VkDeviceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		createInfo.pQueueCreateInfos = queueCreateInfos.data();
		createInfo.queueCreateInfoCount = static_cast<u32>(queueCreateInfos.size());
		createInfo.pEnabledFeatures = &deviceFeatures;
		createInfo.enabledExtensionCount = static_cast<u32>(m_deviceExtensions.size());
		createInfo.ppEnabledExtensionNames = m_deviceExtensions.data();

		// if debug, enable validation layers
#if DEBUG
		// no need to check if validation layers are supported. We already checked it in SetupInstance.
		createInfo.enabledLayerCount = static_cast<u32>(m_validationLayers.size());
		createInfo.ppEnabledLayerNames = m_validationLayers.data();
#else
		createInfo.enabledLayerCount = 0;
#endif

		// create device
		if (vkCreateDevice(m_physicalDevice, &createInfo, nullptr, &m_device) != VK_SUCCESS)
		{
			std::string msg = "VulkanRenderer::SetupLogicalDevice: Failed to create logical device!";
			LOG(msg.c_str());
			BREAKPOINT();
			throw std::runtime_error(msg);
		}

		// get queue
		vkGetDeviceQueue(m_device, m_queueFamilyIndices.GraphicsFamily.value(), 0, &m_graphicsQueue);
		vkGetDeviceQueue(m_device, m_queueFamilyIndices.PresentFamily.value(), 0, &m_presentQueue);
	}

	bool VulkanRenderer::CheckDeviceExtensionSupport(VkPhysicalDevice device)
	{
		u32 extensionCount;
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

		std::vector<VkExtensionProperties> availableExtensions(extensionCount);
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

		std::set<std::string> requiredExtensions(m_deviceExtensions.begin(), m_deviceExtensions.end());

		for (const auto &extension : availableExtensions)
		{
			requiredExtensions.erase(extension.extensionName);
		}

		return requiredExtensions.empty();
	}

	VulkanSwapChainSupportDetails VulkanRenderer::QuerySwapChainSupport(VkPhysicalDevice device)
	{
		VulkanSwapChainSupportDetails details;

		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, m_surface, &details.Capabilities);

		u32 formatCount;
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_surface, &formatCount, nullptr);

		if (formatCount != 0)
		{
			details.Formats.resize(formatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_surface, &formatCount, details.Formats.data());
		}
		else
		{
			LOG("VulkanRenderer::QuerySwapChainSupport: No surface formats found!\n");
		}

		u32 presentModeCount;
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_surface, &presentModeCount, nullptr);

		if (presentModeCount != 0)
		{
			details.PresentModes.resize(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_surface, &presentModeCount, details.PresentModes.data());
		}
		else
		{
			LOG("VulkanRenderer::QuerySwapChainSupport: No present modes found!\n");
		}

		return details;
	}

	VkSurfaceFormatKHR VulkanRenderer::ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats)
	{
		for (const VkSurfaceFormatKHR &availableFormat : availableFormats)
		{
			if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
			{
				return availableFormat;
			}
		}

		return availableFormats[0];
	}

	VkPresentModeKHR VulkanRenderer::ChooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes)
	{
		for (const VkPresentModeKHR &availablePresentMode : availablePresentModes)
		{
			if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
			{
				return availablePresentMode;
			}
		}

		return VK_PRESENT_MODE_FIFO_KHR;
	}

	VkExtent2D VulkanRenderer::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities)
	{
		if (capabilities.currentExtent.width != UINT32_MAX)
		{
			return capabilities.currentExtent;
		}
		else
		{
			Vec2i windowSize = m_windowManager->GetWindowSize();

			VkExtent2D actualExtent = {
				static_cast<u32>(windowSize.X),
				static_cast<u32>(windowSize.Y)};

			actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
			actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

			LOG("VulkanRenderer::ChooseSwapExtent: Chosen swap extent: %d x %d\n", actualExtent.width, actualExtent.height);

			return actualExtent;
		}
	}

	void VulkanRenderer::SetupSwapChain()
	{
		VulkanSwapChainSupportDetails swapChainSupport = QuerySwapChainSupport(m_physicalDevice);

		VkSurfaceFormatKHR surfaceFormat = ChooseSwapSurfaceFormat(swapChainSupport.Formats);
		VkPresentModeKHR presentMode = ChooseSwapPresentMode(swapChainSupport.PresentModes);
		VkExtent2D extent = ChooseSwapExtent(swapChainSupport.Capabilities);

		// The minimum number of images in the swap chain. We try to have one more than the minimum.
		u32 imageCount = swapChainSupport.Capabilities.minImageCount + 1;
		// Do not exceed the maximum image count.
		if (swapChainSupport.Capabilities.maxImageCount > 0 && imageCount > swapChainSupport.Capabilities.maxImageCount)
		{
			imageCount = swapChainSupport.Capabilities.maxImageCount;
		}

		VkSwapchainCreateInfoKHR createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.surface = m_surface;
		createInfo.minImageCount = imageCount;
		createInfo.imageFormat = surfaceFormat.format;
		createInfo.imageColorSpace = surfaceFormat.colorSpace;
		// The resolution of the swap chain images. We use the window's resolution.
		createInfo.imageExtent = extent;
		createInfo.imageArrayLayers = 1;							 // always 1 unless we are developing a stereoscopic 3D application.
		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT; // we render directly to the images

		VulkanQueueFamilyIndices indices;
		FindValidQueueFamilyIndices(m_physicalDevice, &indices);
		u32 queueFamilyIndices[] = {indices.GraphicsFamily.value(), indices.PresentFamily.value()};

		if (indices.GraphicsFamily != indices.PresentFamily)
		{
			// If the graphics and present queues are from different queue families, we either have to explicitly transfer ownership of images between them, or we have to create the swap chain with imageSharingMode set to VK_SHARING_MODE_CONCURRENT.
			createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = 2; // number of queue families
			createInfo.pQueueFamilyIndices = queueFamilyIndices;
		}
		else
		{
			// If the graphics and present queues are from the same family, which they are most of the time, we should stick to exclusive mode, because concurrent mode requires you to specify ownership of each image every time you want to use it, which is a lot of work for no real benefit.
			createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
			createInfo.queueFamilyIndexCount = 0;	  // Optional
			createInfo.pQueueFamilyIndices = nullptr; // Optional
		}

		// We can specify that a certain transform should be applied to images in the swap chain if it is supported (supportedTransforms in capabilities), like a 90 degree clockwise rotation or horizontal flip.
		createInfo.preTransform = swapChainSupport.Capabilities.currentTransform;

		// The compositeAlpha field specifies if the alpha channel should be used for blending with other windows in the window system. You'll almost always want to simply ignore the alpha channel, hence VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR.
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

		// The presentMode member specifies the presentation mode, which is the condition for "swapping" images to the screen. There are four possible modes:
		// VK_PRESENT_MODE_IMMEDIATE_KHR: Images submitted by your application are transferred to the screen right away, which may result in tearing.
		// VK_PRESENT_MODE_FIFO_KHR: The swap chain is a queue where the display takes an image from the front of the queue when the display is refreshed and the program inserts rendered images at the back of the queue. If the queue is full then the program has to wait. This is most similar to vertical sync as found in modern games. The moment that the display is refreshed is known as "vertical blank".
		// VK_PRESENT_MODE_FIFO_RELAXED_KHR: This mode only differs from the previous one if the application is late and the queue was empty at the last vertical blank. Instead of waiting for the next vertical blank, the image is transferred right away when it finally arrives. This may result in visible tearing.
		// VK_PRESENT_MODE_MAILBOX_KHR: This is another variation of the second mode. Instead of blocking the application when the queue is full, the images that are already queued are simply replaced with the newer ones. This mode can be used to implement triple buffering, which allows you to avoid tearing with significantly less latency issues than standard vertical sync that uses double buffering.
		createInfo.presentMode = presentMode;

		// The clipped member specifies whether we care about the color of pixels that are obscured, for example because another window is in front of them. If the value is VK_TRUE, then colors of obscured pixels may be undefined. Unless you really need to be able to read these colors, you'll get the best performance by enabling clipping.
		createInfo.clipped = VK_TRUE;

		// The oldSwapchain member allows you to specify a swap chain that should be replaced with the new one we are creating. This is useful when the window is resized, for example. The swap chain will often not be able to simply reuse the same buffers, because their size will no longer match. In that case the swap chain actually needs to be recreated from scratch and the old one passed in here. We're not doing that yet, so we'll simply specify the value VK_NULL_HANDLE.
		createInfo.oldSwapchain = VK_NULL_HANDLE;

		// create swap chain
		if (vkCreateSwapchainKHR(m_device, &createInfo, nullptr, &m_swapChain) != VK_SUCCESS)
		{
			std::string msg = "VulkanRenderer::SetupSwapChain: Failed to create swap chain!";
			LOG(msg.c_str());
			BREAKPOINT();
			throw std::runtime_error(msg);
		}

		// get swap chain images
		vkGetSwapchainImagesKHR(m_device, m_swapChain, &imageCount, nullptr);
		m_swapChainImages.resize(imageCount);
		vkGetSwapchainImagesKHR(m_device, m_swapChain, &imageCount, m_swapChainImages.data());

		// save format and extent
		m_swapChainImageFormat = surfaceFormat.format;
		m_swapChainExtent = extent;

		LOG("VulkanRenderer::SetupSwapChain: Swap chain created.\n");
	}

	void VulkanRenderer::SetupSwapChainImageViews()
	{
		m_swapChainImageViews.resize(m_swapChainImages.size());

		for (size_t i = 0; i < m_swapChainImages.size(); i++)
		{
			VkImageViewCreateInfo createInfo{};
			createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			createInfo.image = m_swapChainImages[i];

			createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
			createInfo.format = m_swapChainImageFormat;

			createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

			createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			createInfo.subresourceRange.baseMipLevel = 0;
			createInfo.subresourceRange.levelCount = 1;
			createInfo.subresourceRange.baseArrayLayer = 0;
			createInfo.subresourceRange.layerCount = 1;

			if (vkCreateImageView(m_device, &createInfo, nullptr, &m_swapChainImageViews[i]) != VK_SUCCESS)
			{
				std::string msg = "VulkanRenderer::SetupSwapChainImageViews: Failed to create image views!";
				LOG(msg.c_str());
				BREAKPOINT();
				throw std::runtime_error(msg);
			}
		}
	}

	void VulkanRenderer::SetupRenderPass()
	{
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
	}

	void VulkanRenderer::SetupFramebuffers()
	{
		m_framebuffers = VulkanUtil::Framebuffer.Create(m_device, m_renderPass, m_swapChainImageViews, m_swapChainExtent);
	}

	void VulkanRenderer::SetupCommandPool()
	{
		m_commandPool = VulkanUtil::CommandPool.Create(m_device, m_queueFamilyIndices.GraphicsFamily.value());
	}

	void VulkanRenderer::SetupCommandBuffer()
	{
		m_commandBuffer = VulkanUtil::CommandBuffer.Create(m_device, m_commandPool, VK_COMMAND_BUFFER_LEVEL_PRIMARY);
	}

	void VulkanRenderer::RecordCommandBuffer(VkCommandBuffer commandBuffer, u32 imageIndex)
	{
		VkCommandBufferBeginInfo beginInfo = VulkanUtil::CommandBufferBeginInfo.Create();
		if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS)
		{
			std::string msg = "VulkanRenderer::RecordCommandBuffer: Failed to begin recording command buffer!";
			LOG(msg.c_str());
			BREAKPOINT();
			throw std::runtime_error(msg);
		}

		// Clear color
		VkClearValue clearColor = {ClearColor.R, ClearColor.G, ClearColor.B, ClearColor.A};

		VkRenderPassBeginInfo renderPassInfo = VulkanUtil::RenderPassBeginInfo.Create(m_renderPass, m_framebuffers[imageIndex], m_swapChainExtent, clearColor);

		// start render pass
		vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

		// Viewport
		VkViewport viewport = VulkanUtil::Viewport.Create(m_swapChainExtent);
		vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

		// Scissor
		VkRect2D scissor{};
		scissor.offset = {0, 0};
		scissor.extent = m_swapChainExtent;
		vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

		// DRAW

		// end render pass
		vkCmdEndRenderPass(commandBuffer);

		// end recording
		if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS)
		{
			std::string msg = "VulkanRenderer::RecordCommandBuffer: Failed to record command buffer!";
			LOG(msg.c_str());
			BREAKPOINT();
			throw std::runtime_error(msg);
		}
	}

	void VulkanRenderer::SetupSyncObjects()
	{
		m_imageAvailableSemaphore = VulkanUtil::Semaphore.Create(m_device);
		m_renderFinishedSemaphore = VulkanUtil::Semaphore.Create(m_device);
		m_inFlightFence = VulkanUtil::Fence.Create(m_device);
	}

	void VulkanRenderer::Initialize(const std::vector<std::string> &requiredExtensions)
	{
		SetupInstance(requiredExtensions);
		SetupSurface();
#if DEBUG
		SetupDebugUtilsMessengerEXT();
#endif
		SetupPhysicalDevice();
		SetupLogicalDevice();
		SetupSwapChain();
		SetupSwapChainImageViews();
		SetupRenderPass();
		SetupFramebuffers();
		SetupCommandPool();
		SetupCommandBuffer();
		SetupSyncObjects();

		return;
	}

	void VulkanRenderer::BeginDraw()
	{
		vkAcquireNextImageKHR(m_device, m_swapChain, UINT64_MAX, m_imageAvailableSemaphore, VK_NULL_HANDLE, &m_currentFrameIndex);
		if (vkResetCommandBuffer(m_commandBuffer, 0) != VK_SUCCESS)
		{
			std::string msg = "VulkanRenderer::BeginDraw: Failed to reset command buffer!";
			LOG(msg.c_str());
			BREAKPOINT();
			throw std::runtime_error(msg);
		}
		RecordCommandBuffer(m_commandBuffer, m_currentFrameIndex);
	}

	void VulkanRenderer::EndDraw()
	{

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

		//// present
		VkPresentInfoKHR presentInfo{};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

		// Wait on these semaphores before presenting. This waits until the render is finished.
		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = &m_renderFinishedSemaphore;

		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = &m_swapChain;
		presentInfo.pImageIndices = &m_currentFrameIndex;

		presentInfo.pResults = nullptr; // Optional

		//// present
		vkQueuePresentKHR(m_presentQueue, &presentInfo);

		// wait for fence. This waits until the render is finished. It syncs the CPU and GPU.
		vkWaitForFences(m_device, 1, &m_inFlightFence, VK_TRUE, UINT64_MAX);
		vkResetFences(m_device, 1, &m_inFlightFence);
	}

	void VulkanRenderer::Destroy()
	{

		// create instance
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