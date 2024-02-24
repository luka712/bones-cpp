#ifndef BNS_TEXTURE_FACTORY_INTERFACE_HPP

#define BNS_TEXTURE_FACTORY_INTERFACE_HPP

#include "texture/bns_texture2d.hpp"
#include "ImageLoader.hpp"
#include <map>

namespace bns
{
    class Framework;

    struct TextureOptions
    {
        TextureOptions();

        /// @brief The texture usage. By default, it is set to TextureUsage::CopyDst_TextureBinding.
        TextureUsage TextureUsage;

        /// @brief The texture format. By default, it is set to TextureFormat::RGBA_8_Unorm.
        TextureFormat Format;

        /// @brief The min filter.
        SamplerMinFilter MinFilter;

        /// @brief The mag filter.
        SamplerMagFilter MagFilter;
    };

    class TextureManager
    {
    protected:
        ImageLoader *m_imageLoader;

        /// @brief The texture cache.
        std::map<std::string, Texture2D *> m_textureCache;

        /// @brief The implementation of this should just create a texture instance according to the backend renderer being used.
        /// In short it should be WebGPU, Metal, OpenGL, Vulkan or DirectX Texture2D implementation
        /// @param imageData The image data.
        /// @param textureUsage The texture usage.
        /// @param format The texture format.
        /// @param samplerMinFilter The min filter. By default, it is set to SamplerMinFilter::LINEAR.
        /// @param samplerMagFilter The mag filter. By default, it is set to SamplerMagFilter::LINEAR.
        /// @return The texture instance.
        virtual Texture2D *CreateBackendImplTexture(ImageData *imageData, TextureUsage textureUsage, TextureFormat format,
                                                    SamplerMinFilter samplerMinFilter = SamplerMinFilter::LINEAR,
                                                    SamplerMagFilter samplerMagFilter = SamplerMagFilter::LINEAR) = 0;

    public:
        /// @brief Construct a new TextureManager object
        TextureManager(ImageLoader *imageLoader);

        /// @brief Load a texture.
        /// @param path The path to the texture.
        /// @param key The key to cache texture by. If not specified, texture is not cached.
        /// @param options The texture options. @see TextureOptions.
        Texture2D *LoadTexture2D(std::string path,
                                 std::string key = "",
                                 TextureOptions *options = nullptr);

        /// @brief Create a texture.
        /// @param imageData The image data.
        /// @param textureUsageF The texture usage flags. By default, it is set to TextureUsage::CopyDst_TextureBinding.
        /// @param format The texture format. By default, it is set to TextureFormat::RGBA_8_Unorm.
        /// @param samplerMinFilter The min filter. By default, it is set to SamplerMinFilter::LINEAR.
        /// @param samplerMagFilter The mag filter. By default, it is set to SamplerMagFilter::LINEAR.
        /// @param key The key to cache texture by. If not specified, texture is not cached.
        /// @return
        Texture2D *CreateTexture(ImageData *imageData,
                                 TextureUsage textureUsageFlags = TextureUsage::CopyDst_TextureBinding,
                                 TextureFormat format = TextureFormat::RGBA_8_Unorm,
                                 SamplerMinFilter samplerMinFilter = SamplerMinFilter::LINEAR, SamplerMagFilter samplerMagFilter = SamplerMagFilter::LINEAR,
                                 std::string key = "");

        /**
         * @brief Create an empty texture.
         * @param width The width.
         * @param height The height.
         * @param textureUsageFlags The texture usage flags. By default, it is set to TextureUsage::CopyDst_TextureBinding_RenderAttachment.
         * @param format The texture format. By default, it is set to TextureFormat::RGBA_8_Unorm.
         * @return Texture2D* The texture.
         */
        Texture2D *CreateEmpty(u32 width, u32 height,
                               TextureUsage textureUsageFlags = TextureUsage::CopyDst_TextureBinding_RenderAttachment,
                               TextureFormat format = TextureFormat::RGBA_8_Unorm);
    };
}

#endif // !BNS_TEXTURE_FACTORY_INTERFACE_HPP