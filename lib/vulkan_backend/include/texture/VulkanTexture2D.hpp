#if USE_VULKAN

#ifndef BNS_VULKAN_TEXTURE_2D_HPP

#define BNS_VULKAN_TEXTURE_2D_HPP

#include "texture/Texture2D.hpp"
#include "ImageData.hpp"
#include "BnsVulkan.hpp"
#include "VulkanUtil.hpp"

namespace bns
{
    class VulkanTexture2D final : public Texture2D
    {
    private:
        /// @brief The vulkan physical device.
        VkPhysicalDevice m_physicalDevice;

        /// @brief The device.
        VkDevice m_device;

        /// @brief The command pool.
        VkCommandPool m_commandPool;

        /// @brief The graphics queue.
        VkQueue m_graphicsQueue;

        /// @brief The image.
        VkImage m_image;

        /// @brief The image memory.
        VkDeviceMemory m_imageMemory;

        /// @brief Temporary image data.
        ImageData *m_imageData;

        /**
         * @brief Convert the texture usage flags to Vulkan texture usage flags.
         */
        //  WGPUTextureUsage Convert(i32 textureUsageFlags) const;

        /**
         * @brief Convert the texture format to Vulkan texture format.
         */
        // WGPUTextureFormat Convert(TextureFormat format) const;

    public:
        /**
         * @brief The sampler. Exposed so that it can be used by shader, when creating texture bind group.
         */
        // WGPUSampler Sampler;

        /**
         * @brief The texture. Exposed so that it can be used by shader, when creating texture bind group.
         */
        // WGPUTexture Texture;

        /// @brief The constructor.
        /// @param physicalDevice The physical device.
        /// @param device The device.
        /// @param commandPool The command pool.
        /// @param graphicsQueue The graphics queue.
        /// @param imageData The image data.
        /// @param textureUsageFlags The texture usage flags.
        /// @param format The texture format.
        VulkanTexture2D(const VkPhysicalDevice &physicalDevice,
                        const VkDevice &device,
                        const VkCommandPool &commandPool,
                        const VkQueue &graphicsQueue,
                        ImageData *imageData, i32 textureUsageFlags, TextureFormat format);
        /// @brief The destructor.
        ~VulkanTexture2D();

        /**
         * Creates the texture view.
         */
        // inline WGPUTextureView CreateView() const
        // {
        //     WGPUTextureViewDescriptor textureViewDesc = VulkanUtil::TextureViewDescriptor.Create("Texture view: " + std::to_string(m_id));
        //     textureViewDesc.format = Convert(m_format);
        //     WGPUTextureView textureView = wgpuTextureCreateView(Texture, &textureViewDesc);
        //     return textureView;
        // }

        /// @brief Initialize the texture.
        void Initialize() override;

        /// @brief Destroy the texture.
        void Release() override;
    };
}

#endif // !BNS_Vulkan_TEXTURE_2D_HPP

#endif // USE_Vulkan