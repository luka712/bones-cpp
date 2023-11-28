#if USE_VULKAN

#ifndef BNS_VULKAN_RENDERER_HPP

#define BNS_VULKAN_RENDERER_HPP

#include "renderer/Renderer.hpp"
#include "BnsVulkan.hpp"
#include "Window.hpp"
#include <optional>

namespace bns
{
    struct VulkanQueueFamilyIndices
    {
        /// @brief The graphics queue family index.
        std::optional<u32> GraphicsFamily;

        /// @brief The present queue family index.
        std::optional<u32> PresentFamily;

        /// @brief Checks if the queue family indices are valid.
        /// @return True if the queue family indices are valid, false otherwise.
        inline bool IsValid() const
        {
            return GraphicsFamily.has_value() && PresentFamily.has_value();
        }
    };

    struct VulkanSwapChainSupportDetails
    {
        /// @brief The surface capabilities.
        VkSurfaceCapabilitiesKHR Capabilities;

        /// @brief The surface formats.
        std::vector<VkSurfaceFormatKHR> Formats;

        /// @brief The present modes.
        std::vector<VkPresentModeKHR> PresentModes;

        /// @brief Checks if the swap chain support details are valid.
        /// @return True if the swap chain support details are valid, false otherwise.
        inline bool IsValid() const
        {
            return !Formats.empty() && !PresentModes.empty();
        }
    };

    class VulkanRenderer final : public Renderer
    {
    private:
        /// @brief The window manager.
        WindowManager *m_windowManager;

/// The validation layers
#if DEBUG
        const std::vector<const char *> m_validationLayers = {
            "VK_LAYER_KHRONOS_validation"};
#else
        const std::vector<const char *> m_validationLayers = {};
#endif

        /// @brief The required device extensions.
        const std::vector<const char *> m_deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME};

        /// @brief The Vulkan instance.
        VkInstance m_instance;

        /// @brief The Vulkan surface.
        VkSurfaceKHR m_surface;

        /// @brief The Vulkan debug messenger.
        VkDebugUtilsMessengerEXT m_debugMessenger;

        /// @brief Available devices
        std::vector<VkPhysicalDevice> m_availableDevices;

        /// @brief The current Vulkan physical device.
        VkPhysicalDevice m_physicalDevice;

        /// @brief The Vulkan queue family indices.
        VulkanQueueFamilyIndices m_queueFamilyIndices;

        /// @brief The Vulkan logical device.
        VkDevice m_device;

        /// @brief The Vulkan graphics queue.
        VkQueue m_graphicsQueue;

        /// @brief The Vulkan present queue.
        VkQueue m_presentQueue;

        /// @brief The Vulkan swap chain.
        VkSwapchainKHR m_swapChain;

        /// @brief The Vulkan swap chain image format.
        VkFormat m_swapChainImageFormat;

        /// @brief The Vulkan swap chain extent.
        VkExtent2D m_swapChainExtent;

        /// @brief The Vulkan swap chain images.
        std::vector<VkImage> m_swapChainImages;

        /// @brief The Vulkan swap chain image views.
        std::vector<VkImageView> m_swapChainImageViews;

        /// @brief Setups and create an instance internally.
        /// @param requiredWindowExtensions The required window extensions. This should be provided by the window manager.
        void SetupInstance(const std::vector<std::string> &requiredWindowExtensions);

        /// @brief Sets up the surface.
        void SetupSurface();

        /// @brief Checks if the layer is supported.
        /// @param layer The layer to check.
        /// @return True if the layer is supported, false otherwise.
        bool IsLayerSupported(const std::string &layer);

        /// @brief The debug messenger callback.
        /// @param messageSeverity The message severity.
        /// @param messageType The message type.
        /// @param pCallbackData The callback data.
        /// @param pUserData The user data.
        /// @return The result.
        static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                            VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                            const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
                                                            void *pUserData);

        /// @brief Creates and setups the debug messenger.
        void SetupDebugUtilsMessengerEXT();

        /// @brief Finds the available devices and selects the best one.
        void SetupPhysicalDevice();

        /// @brief Sets up the queue family indices.
        /// @param device The physical device.
        /// @param outQueueFamilyIndices The queue family indices to set.
        /// @return True if the queue family indices are valid, false otherwise.
        bool FindValidQueueFamilyIndices(VkPhysicalDevice device, VulkanQueueFamilyIndices *outQueueFamilyIndices);

        /// @brief Sets up the logical device.
        void SetupLogicalDevice();

        /// @brief Checks if the device extension is supported.
        /// @param device The physical device.
        /// @return True if the device extension is supported, false otherwise.
        bool CheckDeviceExtensionSupport(VkPhysicalDevice device);

        /// @brief Gets the swap chain support details.
        /// @param device The physical device.
        /// @return The swap chain support details.
        VulkanSwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);

        /// @brief Chooses the swap surface format.
        /// @param availableFormats The available formats.
        /// @return The swap surface format.
        VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);

        /// @brief Chooses the swap present mode.
        /// @param availablePresentModes The available present modes.
        /// @return The swap present mode.
        VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);

        /// @brief Chooses the swap extent.
        /// @param capabilities The capabilities.
        /// @return The swap extent.
        VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);

        /// @brief Sets up the swap chain.
        void SetupSwapChain();

        /// @brief Sets up the swap chain image views.
        void SetupSwapChainImageViews();

        void Resize();

    public:
        /// @brief Gets the renderer type.
        /// @return The renderer type.
        RendererType GetRendererType() const override { return RendererType::Vulkan; }

        VulkanRenderer(WindowManager *windowManager);

        /// @brief Initialize the renderer.
        /// @param requiredWindowExtensions The required window extensions. In other words these are provided by the window manager and windowing system.
        void Initialize(const std::vector<std::string> &requiredWindowExtensions);
        void BeginDraw() override;
        void EndDraw() override;
        void Destroy() override;

        /**
         * @brief Gets the view into swap chain texture.
         */
        void *GetSwapChainTexture() override;
    };
}

#endif // !BNS_VULKAN_RENDERER_HPP

#endif // USE_VULKAN