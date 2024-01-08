// #if USE_VULKAN


// #ifndef BNS_VULKAN_TEXTURE_2D_HPP

// #define BNS_VULKAN_TEXTURE_2D_HPP

// #include "texture/Texture2D.hpp"
// #include "ImageData.hpp"
// #include "BnsVulkan.hpp"
// #include "VulkanUtil.hpp"

// namespace bns
// {
//     class VulkanTexture2D final : public Texture2D
//     {
//     private:
//         /// @brief The device.
//         WGPUDevice m_device;

//         /// @brief Host buffer. We copy texture contents to it so that we can use it to create texture.
//         VkBuffer m_stagingBuffer;

//         /// @brief The memory of a staging buffer.
//         VkDeviceMemory m_stagingBufferMemory;
     
//         /**
//          * Temporary image data. To be released by user after texture is initialized.
//          */
//         ImageData *m_imageData;

//         /**
//          * @brief Convert the texture usage flags to Vulkan texture usage flags.
//          */
//         WGPUTextureUsage Convert(i32 textureUsageFlags) const;

//         /**
//          * @brief Convert the texture format to Vulkan texture format.
//         */
//         WGPUTextureFormat Convert(TextureFormat format) const;

//     public:
//         /**
//          * @brief The sampler. Exposed so that it can be used by shader, when creating texture bind group.
//          */
//         WGPUSampler Sampler;

//         /**
//          * @brief The texture. Exposed so that it can be used by shader, when creating texture bind group.
//          */
//         WGPUTexture Texture;

//         /**
//          * @brief The constructor.
//          */
//         VulkanTexture2D(WGPUDevice device, ImageData *imageData, i32 textureUsageFlags, TextureFormat format);

//         inline ~VulkanTexture2D()
//         {
//             Release();
//         }

//         /**
//          * Creates the texture view.
//          */
//         inline WGPUTextureView CreateView() const
//         {
//             WGPUTextureViewDescriptor textureViewDesc
//                 = VulkanUtil::TextureViewDescriptor.Create("Texture view: " + std::to_string(m_id));
//             textureViewDesc.format = Convert(m_format);
//             WGPUTextureView textureView = wgpuTextureCreateView(Texture, &textureViewDesc);
//             return textureView;
//         }

//         /**
//          * @brief Initialize the texture.
//          */
//         void Initialize() override;

//         /// @brief Destroy the texture.
//         void Release() override;
//     };
// }

// #endif // !BNS_Vulkan_TEXTURE_2D_HPP

// #endif // USE_Vulkan