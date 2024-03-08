
#ifndef BNS_TEXTURE_2D_HPP

#define BNS_TEXTURE_2D_HPP

#include "bns_types.hpp"
#include "bns_rendering_backend_types.hpp"

namespace bns
{
    /// @brief The texture 2D.
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