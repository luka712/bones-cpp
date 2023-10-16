#include "textures/Texture2D.hpp"
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

    Texture2D::Texture2D(i32 width, i32 height, i32 textureUsageFlags, TextureFormat format)
        : m_width(width), m_height(height), m_textureUsageFlags(textureUsageFlags), m_format(format)
    {
        m_lifecycleState = LifecycleState::Created;
        m_id = GenerateID();
    }

    Texture2D::~Texture2D()
    {
#if DEBUG
        std::cout << "Texture2D::~Texture2D() " << m_id << std::endl;
#endif
    }
}