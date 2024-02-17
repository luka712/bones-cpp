#if USE_WEBGPU


#ifndef BNS_WEBGPU_TEXTURE_2D_HPP

#define BNS_WEBGPU_TEXTURE_2D_HPP

#include "texture/Texture2D.hpp"
#include "ImageData.hpp"
#include "bns_webgpu.hpp"
#include "bns_webgpu_util.hpp"

namespace bns
{
    class WebGPUTexture2D final : public Texture2D
    {
    private:
        /// @brief The device.
        WGPUDevice m_device;
     
        /**
         * Temporary image data. To be released by user after texture is initialized.
         */
        ImageData *m_imageData;

        /**
         * @brief Convert the texture usage flags to WebGPU texture usage flags.
         */
        WGPUTextureUsage Convert(i32 textureUsageFlags) const;

        /**
         * @brief Convert the texture format to WebGPU texture format.
        */
        WGPUTextureFormat Convert(TextureFormat format) const;

    public:
        /**
         * @brief The sampler. Exposed so that it can be used by shader, when creating texture bind group.
         */
        WGPUSampler Sampler;

        /**
         * @brief The texture. Exposed so that it can be used by shader, when creating texture bind group.
         */
        WGPUTexture Texture;

        /**
         * @brief The constructor.
         */
        WebGPUTexture2D(WGPUDevice device, ImageData *imageData, i32 textureUsageFlags, TextureFormat format);

        inline ~WebGPUTexture2D()
        {
            Release();
        }

        /// @brief Creates the texture view.
        /// @return The texture view.
        WGPUTextureView CreateView() const;
        /**
         * @brief Initialize the texture.
         */
        void Initialize() override;

        /// @brief Destroy the texture.
        void Release() override;
    };
}

#endif // !BNS_WEBGPU_TEXTURE_2D_HPP

#endif // USE_WEBGPU