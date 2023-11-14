
#ifndef BNS_TEXTURE_2D_HPP

#define BNS_TEXTURE_2D_HPP

#include "Types.hpp"

namespace bns
{
    /**
     * @brief The usage of the texture.
     * For WebGPU usage see https://developer.mozilla.org/en-US/docs/Web/API/GPUTexture/usage
     */
    enum TextureUsage
    {
        /**
         * @brief The texture can be used as the source of a copy operation. For example copy texture to buffer.
         */
        COPY_SRC = 0x1,

        /**
         * @brief The texture can be used as the destination of a copy operation. For example copy buffer to texture.
         */
        COPY_DST = 0x2,

        /**
         * @brief The texture can be used as a sampled texture in a shader.
         * For example as a resource when in bind group entry, which adheres to a entry specified with texture binding layout.
         */
        TEXTURE_BINDING = 0x4,

        /**
         * @brief The texture can be used as a storage texture in a shader.
         * For example as a resource when in bind group entry, which adheres to a entry specified with storage texture binding layout.
         */
        TEXTURE_STORAGE = 0x8,

        /**
         * @brief The texture can be used as a color or depth/stencil attachment in render pass.
         */
        RENDER_ATTACHMENT = 0x10,
    };

    /**
     * @brief The format of the texture.
     * For WebGPU formats see https://gpuweb.github.io/gpuweb/#enumdef-gputextureformat
     */
    enum class TextureFormat
    {
        /**
         * Ordinary format with four 8-bit normalized unsigned integer components in RGBA order.
         */
        RGBA_8_Unorm = 0x1,
        /**
         * Ordinary format with four 8-bit normalized unsigned integer components in BGRA order.
         */
        BGRA_8_Unorm = 0x2,
    };

    class Texture2D
    {
    protected:
        LifecycleState m_lifecycleState;

        u32 m_id;
        i32 m_width;
        i32 m_height;

        /**
         * @brief The usage of the texture.
         */
        i32 m_textureUsageFlags;

        /**
         * @brief The format of the texture.
         */
        TextureFormat m_format;

        /**
         * The id generator for the textures. Is increased whenever a new texture is created.
         */
        static u32 s_idGenerator;

        /**
         * @brief Generates a new id for the texture.
         */
        static u32 GenerateID();

    public:
        Texture2D(i32 width, i32 height, i32 textureUsageFlags, TextureFormat format);

        virtual ~Texture2D();

        /**
         * @brief The id of the texture.
         */
        inline u32 GetID() const { return m_id; }

        /**
         * @brief The width of the texture.
         */
        inline i32 GetWidth() const { return m_width; }

        /**
         * @brief The height of the texture.
         */
        inline i32 GetHeight() const { return m_height; }

        /**
         * @brief Initialize the texture.
         */
        virtual void Initialize() = 0;

        /// @brief Release the texture.
        virtual void Release() = 0;
    };
}

#endif