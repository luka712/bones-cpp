#ifndef BNS_METAL_TEXTURE_2D_HPP

#define BNS_METAL_TEXTURE_2D_HPP

#include "textures/Texture2D.hpp"
#include "loaders/ImageLoader.hpp"
#include <Metal/Metal.hpp>

namespace bns
{
    class Framework;

    class MetalTexture2D final : public Texture2D
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
        MTL::SamplerState* Sampler;

        /**
         * @brief The texture. Exposed so that it can be used by shader, when creating texture bind group.
         */
        MTL::Texture *Texture;

        /**
         * @brief The constructor.
         */
        MetalTexture2D(Framework &framework, ImageData *imageData);

        /**
         * @brief Initialize the texture.
         */
        void Initialize() override;
    };
}

#endif // !BNS_METAL_TEXTURE_2D_HPP
