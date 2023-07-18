#ifndef BNS_WEBGPU_TEXTURE_2D_HPP

#define BNS_WEBGPU_TEXTURE_2D_HPP

#include "textures/Texture2D.hpp"
#include "loaders/ImageLoader.hpp"
#include <webgpu/webgpu.h>

namespace bns
{
    class Framework;

    class WebGPUTexture2D final : public Texture2D
    {
    private:
        Framework &m_framework;

        /**
         * Temporary image data. To be released by user after texture is initialized.
         */
        ImageData *m_imageData;

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
        WebGPUTexture2D(Framework &framework, ImageData *imageData);

        /**
         * @brief Initialize the texture.
         */
        void Initialize() override;
    };
}

#endif // !BNS_WEBGPU_TEXTURE_2D_HPP
