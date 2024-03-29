#include "texture/bns_texture2d.hpp"
#include "iostream"

namespace bns
{
#pragma region Statics

    u32 Texture2D::s_idGenerator = 0;

    u32 Texture2D::GenerateID()
    {
        return s_idGenerator++;
    }

#pragma endregion

    Texture2D::Texture2D(i32 width, i32 height, TextureUsage textureUsage, TextureFormat format, SamplerMinFilter minFilter, SamplerMagFilter magFilter)
        : m_width(width), m_height(height), m_textureUsage(textureUsage), m_format(format),
          m_minFilter(minFilter), m_magFilter(magFilter)
    {
        m_lifecycleState = LifecycleState::Created;
        m_id = GenerateID();
    }

    Texture2D::~Texture2D()
    {
        LOG("Texture2D::~Texture2D()");
    }
}