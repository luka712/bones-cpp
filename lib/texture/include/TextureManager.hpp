#ifndef BNS_TEXTURE_FACTORY_INTERFACE_HPP

#define BNS_TEXTURE_FACTORY_INTERFACE_HPP

#include "Texture2D.hpp"
#include "ImageLoader.hpp"
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

    class TextureManager 
    {
    protected:
        ImageLoader &m_imageLoader;

        /// @brief The texture cache.
        std::map<std::string, Texture2D *> m_textureCache;

        /// @brief The implementation of this should just create a texture instance according to the backend renderer being used.
        /// In short it should be WebGPU, Metal, OpenGL, Vulkan or DirectX Texture2D implementation
        /// @param imageData The image data.
        /// @param textureUsageFlags The texture usage flags.
        /// @param format The texture format.
        /// @return The texture instance.
        virtual Texture2D* CreateBackendImplTexture(ImageData *imageData, i32 textureUsageFlags, TextureFormat format) = 0;


    public:
        /// @brief Construct a new TextureManager object
        TextureManager(ImageLoader& imageLoader);

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

#endif // !BNS_TEXTURE_FACTORY_INTERFACE_HPP