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

        /// @brief The image view.
        VkImageView m_imageView;

        /// @brief The image sampler.
        VkSampler m_imageSampler;

        /// @brief Temporary image data.
        ImageData *m_imageData;

        /// @brief Convert sampler filter to vulkan filter.
        /// @param filter The sampler filter.
        /// @return The vulkan filter.
        VkFilter SamplerFilterToVulkanFilter(SamplerMinFilter filter);

        /// @brief Convert sampler filter to vulkan filter.
        /// @param filter The sampler filter.
        /// @return The vulkan filter.
        VkFilter SamplerFilterToVulkanFilter(SamplerMagFilter filter);

    public:
        /// @brief The constructor.
        /// @param physicalDevice The physical device.
        /// @param device The device.
        /// @param commandPool The command pool.
        /// @param graphicsQueue The graphics queue.
        /// @param imageData The image data.
        /// @param textureUsageFlags The texture usage flags.
        /// @param format The texture format.
        /// @param minFilter The min filter. By default, it is set to SamplerMinFilter::LINEAR.
        /// @param magFilter The mag filter. By default, it is set to SamplerMagFilter::LINEAR.
        VulkanTexture2D(const VkPhysicalDevice &physicalDevice,
                        const VkDevice &device,
                        const VkCommandPool &commandPool,
                        const VkQueue &graphicsQueue,
                        ImageData *imageData, i32 textureUsageFlags, TextureFormat format,
                        SamplerMinFilter minFilter = SamplerMinFilter::LINEAR, SamplerMagFilter magFilter = SamplerMagFilter::LINEAR);
        /// @brief The destructor.
        ~VulkanTexture2D();

        /// @brief Get the image view.
        const VkImageView &GetImageView() const { return m_imageView; }

        /// @brief Get the image sampler.
        const VkSampler &GetSampler() const { return m_imageSampler; }

        /// @brief Initialize the texture.
        void Initialize() override;

        /// @brief Destroy the texture.
        void Release() override;
    };
}

#endif // !BNS_Vulkan_TEXTURE_2D_HPP

#endif // USE_Vulkan