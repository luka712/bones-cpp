
#ifndef BNS_TEXTURE_2D_HPP

#define BNS_TEXTURE_2D_HPP

#include "bns_types.hpp"

namespace bns
{

    /// @brief The usage of the texture.
    /// For WebGPU usage see https://developer.mozilla.org/en-US/docs/Web/API/GPUTexture/usage
    enum TextureUsage
    {
        /// @brief The texture can be used as the source of a copy operation. For example copy texture to buffer.
        CopySrc = 0x1,

        /// @brief The texture can be used as the destination of a copy operation. For example copy buffer to texture.
        CopyDst = 0x2,

        /// @brief The texture can be used as a sampled texture in a shader.
        /// For example as a resource when in bind group entry, which adheres to a entry specified with texture binding layout.
        TextureBinding = 0x4,

        /// @brief The texture can be used as a storage texture in a shader.
        /// For example as a resource when in bind group entry, which adheres to a entry specified with storage texture binding layout.
        TextureStorage = 0x8,

        /// @brief The texture can be used as a color or depth/stencil attachment in render pass.
        RenderAttachment = 0x10,

        /// @brief Can be used as copy destination and texture binding.
        CopyDst_TextureBinding = CopyDst | TextureBinding,
        /// @brief Can be used as copy destination, texture binding and render attachment.
        CopyDst_TextureBinding_RenderAttachment = CopyDst | TextureBinding | RenderAttachment,
        CopyDst_CopySrc_TextureBinding_RenderAttachment = CopyDst | CopySrc | TextureBinding | RenderAttachment,
    };

    /// @brief The format of the texture.
    enum class TextureFormat
    {
        /// @brief Ordinary format with four 8-bit normalized unsigned integer components in RGBA order.
        RGBA_8_Unorm = 0x1,

        /// @brief Ordinary format with four 8-bit normalized unsigned integer components in BGRA order.
        BGRA_8_Unorm = 0x2,
    };

    /// @brief The min filter.
    enum class SamplerMinFilter
    {
        NEAREST = 0x1,
        LINEAR = 0x2,
        NEAREST_MIPMAP_NEAREST = 0x3,
        LINEAR_MIPMAP_NEAREST = 0x4,
        NEAREST_MIPMAP_LINEAR = 0x5,
        LINEAR_MIPMAP_LINEAR = 0x6,
    };

    /// @brief The mag filter.
    enum class SamplerMagFilter
    {
        NEAREST = 0x1,
        LINEAR = 0x2,
    };

    class Texture2D
    {
    protected:
        LifecycleState m_lifecycleState;

        u32 m_id;
        i32 m_width;
        i32 m_height;

        /// @brief The usage of the texture.
        TextureUsage m_textureUsage;

        /// @brief The format of the texture.
        TextureFormat m_format;

        /// @brief The min filter.
        SamplerMinFilter m_minFilter;

        /// @brief The mag filter.
        SamplerMagFilter m_magFilter;

        /// @brief The id generator for the textures. Increased by one for each texture created.
        static u32 s_idGenerator;

        /// @brief Generates a new id for the texture.
        static u32 GenerateID();

    public:
        /// @brief The constructor.
        /// @param width The width.
        /// @param height The height.
        /// @param textureUsage The texture usage.
        /// @param format The texture format.
        /// @param minFilter The min filter. By default, it is set to SamplerMinFilter::LINEAR.
        /// @param magFilter The mag filter. By default, it is set to SamplerMagFilter::LINEAR.
        Texture2D(i32 width, i32 height, TextureUsage textureUsage, TextureFormat format,
                  SamplerMinFilter minFilter = SamplerMinFilter::LINEAR, SamplerMagFilter magFilter = SamplerMagFilter::LINEAR);

        virtual ~Texture2D();

        /// @brief The id of the texture.
        inline u32 GetID() const { return m_id; }

        /// @brief The width of the texture.
        inline i32 GetWidth() const { return m_width; }

        /// @brief The height of the texture.
        inline i32 GetHeight() const { return m_height; }

        /// @brief Initialize the texture.
        virtual void Initialize() = 0;

        /// @brief Release the texture.
        virtual void Dispose() = 0;
    };
}

#endif