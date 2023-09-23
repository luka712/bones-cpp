#ifndef BNS_WEBGPU_TEXTURE_2D_HPP

#define BNS_WEBGPU_TEXTURE_2D_HPP

#include "textures/Texture2D.hpp"
#include "data/ImageData.hpp"
#include <webgpu/webgpu.h>
#include "util/wgpu/WebGPUTextureViewDescriptorUtil.hpp"

namespace bns
{
    class Framework;

    class WebGPUTexture2D final : public Texture2D
    {
    private:
        const Framework &m_framework;

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
        WebGPUTexture2D(const Framework &framework, ImageData *imageData, i32 textureUsageFlags, TextureFormat format);

        /**
         * Creates the texture view.
         */
        inline WGPUTextureView CreateView() const
        {
            WGPUTextureViewDescriptor textureViewDesc
                = WebGPUTextureViewDescriptorUtil::Create("Texture view: " + std::to_string(m_id));
            textureViewDesc.format = Convert(m_format);
            WGPUTextureView textureView = wgpuTextureCreateView(Texture, &textureViewDesc);
            return textureView;
        }

        /**
         * @brief Initialize the texture.
         */
        void Initialize() override;
    };
}

#endif // !BNS_WEBGPU_TEXTURE_2D_HPP
