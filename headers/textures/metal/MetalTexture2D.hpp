#ifndef BNS_METAL_TEXTURE_2D_HPP

#define BNS_METAL_TEXTURE_2D_HPP

#include "textures/Texture2D.hpp"
#include "data/ImageData.hpp"
#include <Metal/Metal.hpp>

namespace bns
{
    class Framework;

    class MetalTexture2D final : public Texture2D
    {
    private:
        const Framework &m_framework;

        /**
         * Temporary image data. To be released by user after texture is initialized.
         */
        ImageData *m_imageData;

        /**
         * @brief Convert the texture format to Metal texture format.
         */
        MTL::PixelFormat Convert(TextureFormat format) const;

        /**
         * @brief Convert the texture usage flags to Metal texture usage flags.
        */
        MTL::TextureUsage Convert(i32 textureUsageFlags) const;

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
        MetalTexture2D(const Framework &framework, ImageData *imageData,  i32 textureUsageFlags, TextureFormat format);

        inline ~MetalTexture2D()
        {
            Release();
        }

        /**
         * @brief Initialize the texture.
         */
        void Initialize() override;

        /// @brief Release the texture.
        void Release() override;
    };
}

#endif // !BNS_METAL_TEXTURE_2D_HPP
