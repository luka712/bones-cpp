#include "textures/Texture2D.hpp"

namespace bns 
{
    #pragma region Statics

    u32 Texture2D::s_idGenerator = 0;

    u32 Texture2D::GenerateID()
    {
        return s_idGenerator++;
    }

    #pragma endregion

    Texture2D::Texture2D(i32 width, i32 height)
        : m_width(width), m_height(height)
    {
        m_id = GenerateID();
    }
}