#if USE_VULKAN

#ifndef BNS_VULKAN_RENDERER_HPP

#define BNS_VULKAN_RENDERER_HPP

#include "renderer/Renderer.hpp"
#include "BnsVulkan.hpp"
#include "Window.hpp"
#include <optional>

namespace bns
{
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
        const std::vector<std::string> m_validationLayers = {"VK_LAYER_KHRONOS_validation"};
#else
        const std::vector<const char *> m_validationLayers = {};
#endif

        /// @brief The required device extensions.
        /// @note This is the minimum required device extensions.
        /// @note Must support swap chain.
        const std::vector<std::string> m_deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

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
        u32 m_graphicsQueueFamilyIndex;

        /// @brief The Vulkan present queue family index.
        u32 m_presentQueueFamilyIndex;

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

        /// @brief The Vulkan render pass.
        VkRenderPass m_renderPass;

        /// @brief The framebuffers.
        std::vector<VkFramebuffer> m_framebuffers;

        /// @brief The command pool.
        VkCommandPool m_commandPool;

        /// @brief The command buffer
        VkCommandBuffer m_commandBuffer;

        /// @brief The image available semaphore.
        VkSemaphore m_imageAvailableSemaphore;

        /// @brief The render finished semaphore.
        VkSemaphore m_renderFinishedSemaphore;

        /// @brief The in flight fence.
        VkFence m_inFlightFence;

        /// @brief The index of the current frame.
        u32 m_currentFrameIndex;

        /// @brief The resize flag.
        bool m_swapchainOutOfDateFlag;

        // TODO: remove, just for test
        VkPipeline m_pipeline;
        VkPipelineLayout m_pipelineLayout;
        VkBuffer m_vertexBuffer;
        VkDescriptorSet m_descriptorSet;

        /// @brief Setups and create an instance internally.
        /// @param requiredWindowExtensions The required window extensions. This should be provided by the window manager.
        void SetupInstance(const std::vector<std::string> &requiredWindowExtensions);

        /// @brief Creates the swapchain.
        void CreateSwapchain();

        /// @brief Creates the swapchain image views.
        void CreateSwapchainImageViews();

        /// @brief Creates the framebuffers.
        void CreateFramebuffers();

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

        /// @brief Recreate swapchain when needed, such as resize.
        /// @note Also called when @ref vkAcquireNextImageKHR returns VK_ERROR_OUT_OF_DATE_KHR.
        void RecreateSwapchain();

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