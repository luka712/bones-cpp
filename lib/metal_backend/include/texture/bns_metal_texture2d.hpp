#if USE_METAL

#ifndef BNS_METAL_TEXTURE_2D_HPP

#define BNS_METAL_TEXTURE_2D_HPP

#include "texture/bns_texture2d.hpp"
#include "ImageData.hpp"
#include "bns_metal.hpp"
#include "renderer/bns_metal_renderer.hpp"

namespace bns
{
    class MetalTexture2D final : public Texture2D
    {
    private:
        MetalRenderer *m_renderer;

        /// @brief The device.
        MTL::Device *m_device;

        /// @brief Temporary image data. To be released by user after texture is initialized.
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
        /// @brief The sampler. Exposed so that it can be used by shader, when creating texture bind group.
        MTL::SamplerState *Sampler;

        /// @brief The texture. Exposed so that it can be used by shader, when creating texture bind group.
        MTL::Texture *Texture;

        /// @brief The constructor.
        /// @param renderer The renderer.
        /// @param imageData The image data.
        /// @param textureUsage The texture usage.
        /// @param format The texture format.
        MetalTexture2D(Renderer *device, ImageData *imageData, TextureUsage textureUsage, TextureFormat format);

        ~MetalTexture2D();

        /// @brief Initialize the texture.
        void Initialize() override;

        /// @brief Release the texture.
        void Dispose() override;

        /// @brief Create an empty texture of white color.
        /// @param renderer The renderer.
        /// @param width The width.
        /// @param height The height.
        static Texture2D* CreateEmpty(Renderer* renderer, i32 width, i32 height);
    };
}

#endif // !BNS_METAL_TEXTURE_2D_HPP

#endif // __APPLE__
