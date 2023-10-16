#ifndef BNS_TEXTURE_FACTORY_HPP

#define BNS_TEXTURE_FACTORY_HPP

#include "textures/Texture2D.hpp"
#include "loaders/ImageLoader.hpp"
#include <map>

namespace bns
{
    class Framework;

    struct TextureOptions
    {
        TextureOptions();

        /// @brief The texture usage flags. By default, it is set to TextureUsage::TEXTURE_BINDING | TextureUsage::COPY_DST.
        i32 TextureUsageFlags;

        /// @brief The texture format. By default, it is set to TextureFormat::RGBA_8_Unorm.
        TextureFormat Format;
    };

    class TextureManager final
    {
    private:
        Framework &m_framework;

        /// @brief The texture cache.
        std::map<std::string, Texture2D *> m_textureCache;

    public:
        /**
         * @brief Construct a new TextureManager object
         */
        TextureManager(Framework &framework);

        /// @brief Load a texture.
        /// @param path The path to the texture.
        /// @param key The key to cache texture by. If not specified, texture is not cached.
        /// @param options The texture options. @see TextureOptions.
        Texture2D *LoadTexture2D(std::string path,
                                 std::string key = "",
                                 TextureOptions *options = nullptr);

        /// @brief Create a texture.
        /// @param imageData The image data.
        /// @param textureUsageFlags The texture usage flags. By default, it is set to TextureUsage::TEXTURE_BINDING | TextureUsage::COPY_DST.
        /// @param format The texture format. By default, it is set to TextureFormat::RGBA_8_Unorm.
        /// @param key The key to cache texture by. If not specified, texture is not cached.
        /// @return 
        Texture2D *CreateTexture(ImageData *imageData,
                                 i32 textureUsageFlags = TextureUsage::TEXTURE_BINDING | TextureUsage::COPY_DST,
                                 TextureFormat format = TextureFormat::RGBA_8_Unorm,
                                 std::string key = "");

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