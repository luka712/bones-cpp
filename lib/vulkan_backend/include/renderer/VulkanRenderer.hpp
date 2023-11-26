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

        /// @brief Checks if the queue family indices are valid.
        /// @return True if the queue family indices are valid, false otherwise.
        inline bool IsValid() const
        {
            return GraphicsFamily.has_value();
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
    };

    class VulkanRenderer final : public Renderer
    {
    private:
        /// @brief The window manager.
        WindowManager *m_windowManager;

        /// @brief The Vulkan instance.
        VkInstance m_instance;

        /// @brief The Vulkan debug messenger.
        VkDebugUtilsMessengerEXT m_debugMessenger;

        /// @brief Available devices
        std::vector<VkPhysicalDevice> m_availableDevices;

        /// @brief The current Vulkan physical device.
        VkPhysicalDevice m_physicalDevice;

        /// @brief The Vulkan physical device.
        VkDevice m_device;

        /// @brief The Vulkan queue family indices.
        VulkanQueueFamilyIndices m_queueFamilyIndices;     

        /// @brief Setups and create an instance internally.
        /// @param requiredWindowExtensions The required window extensions. This should be provided by the window manager.
        void SetupInstance(const std::vector<std::string> &requiredWindowExtensions);

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


        /// @brief Finds the queue family indices.
        /// @param device The physical device.
        /// @return The queue family indices.
        VulkanQueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);

        /// @brief Sets up the queue family indices.
        void SetupQueueFamilyIndices();

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