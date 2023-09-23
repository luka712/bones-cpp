#ifndef BNS_TEXTURE_FACTORY_HPP

#define BNS_TEXTURE_FACTORY_HPP

#include "textures/Texture2D.hpp"
#include "loaders/ImageLoader.hpp"

namespace bns
{
    class Framework;

    class TextureFactory final
    {
    private:
        const Framework &m_framework;

    public:
        /**
         * @brief Construct a new TextureFactory object
         */
        TextureFactory(const Framework &framework);

        /**
         * @brief Create a texture.
         * @param imageData The image data.
         * @return Texture2D* The texture.
         */
        Texture2D *CreateTexture(ImageData *imageData,
                                 i32 textureUsageFlags = TextureUsage::TEXTURE_BINDING | TextureUsage::COPY_DST,
                                 TextureFormat format = TextureFormat::RGBA_8_Unorm);

        /**
         * @brief Create an empty texture.
         * @param width The width.
         * @param height The height.
         * @param textureUsageFlags The texture usage flags. By default, it is set to TextureUsage::TEXTURE_BINDING | TextureUsage::COPY_DST | TextureUsage::RENDER_ATTACHMENT.
         * @param format The texture format. By default, it is set to TextureFormat::RGBA_8_Unorm.
         * @return Texture2D* The texture.
         */
        Texture2D *CreateEmpty(u32 width, u32 height,
                                                 i32 textureUsageFlags = TextureUsage::TEXTURE_BINDING | TextureUsage::COPY_DST | TextureUsage::RENDER_ATTACHMENT,
                                                 TextureFormat format = TextureFormat::RGBA_8_Unorm);
    };
}

#endif // !BNS_TEXTURE_FACTORY_HPP