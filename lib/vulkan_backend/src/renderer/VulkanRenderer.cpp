#if USE_VULKAN

#include "renderer/VulkanRenderer.hpp"
#include <stdexcept>
#include "CharUtil.hpp"

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
		if (IsLayerSupported("VK_LAYER_KHRONOS_validation"))
		{
			createInfo.enabledLayerCount = 1;
			const char *validationLayer = "VK_LAYER_KHRONOS_validation";
			createInfo.ppEnabledLayerNames = &validationLayer;
		}
		else
		{
			std::string msg = "SDLWindowManager::InitializeForVulkan: Validation layer not supported.";
			LOG(msg.c_str());
			BREAKPOINT();
			throw std::runtime_error(msg.c_str());
		}
#else
		createInfo.enabledLayerCount = 0;
#endif
		// CREATE INSTANCE
		// Create instance and check result.
		VkResult result = vkCreateInstance(&createInfo, nullptr, &m_instance);
		if (result != VK_SUCCESS)
		{
			std::string msg = "SDLWindowManager::InitializeForVulkan: Failed to create Vulkan instance.";
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

			// select first discrete gpu
			if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
			{
				m_physicalDevice = device;
				break;
			}
		}

		// if we didn't find discrete gpu, just select first one.
		if (m_physicalDevice == VK_NULL_HANDLE)
		{
			m_physicalDevice = m_availableDevices[0];
		}
	}

	void VulkanRenderer::SetupQueueFamilyIndices()
	{
		u32 queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevice, &queueFamilyCount, nullptr);

		LOG("VulkanRenderer::SetupQueueFamilyIndices: Found %d queue families.\n", queueFamilyCount);

		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevice, &queueFamilyCount, queueFamilies.data());

		i32 i = 0; 
		for(const VkQueueFamilyProperties& queueFamily : queueFamilies)
		{
			if(queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				m_queueFamilyIndices.GraphicsFamily = i;
				LOG("VulkanRenderer::SetupQueueFamilyIndices: Found graphics queue family at index %d.\n", i);
			}

			// TODO: other families 

			if(m_queueFamilyIndices.IsValid())
			{
				break;
			}

			i++;
		}

		if(!m_queueFamilyIndices.IsValid())
		{
			std::string msg = "VulkanRenderer::SetupQueueFamilyIndices: Failed to find suitable queue family!";
			LOG(msg.c_str());
			BREAKPOINT();
			throw std::runtime_error(msg);
		}
	}

	



	void VulkanRenderer::Initialize(const std::vector<std::string> &requiredExtensions)
	{

		SetupInstance(requiredExtensions);
#if DEBUG
		SetupDebugUtilsMessengerEXT();
#endif
		SetupPhysicalDevice();
		SetupQueueFamilyIndices();

		return;
	}

	void VulkanRenderer::BeginDraw()
	{
	}

	void VulkanRenderer::EndDraw()
	{
	}

	void VulkanRenderer::Destroy()
	{
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