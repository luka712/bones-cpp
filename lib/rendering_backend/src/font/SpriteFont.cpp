#include "font/SpriteFont.hpp"

namespace bns
{
    SpriteFont::SpriteFont(Texture2D *texture)
        : m_texture(texture)
    {
        if (m_texture == nullptr)
            throw std::runtime_error("Texture cannot be null.");
    }

    void SpriteFont::CreateChar(char c, Vec2i size, Vec2i offset, i32 advance, Quad textureCoords)
    {
        m_chars[c] = {size, offset, advance, textureCoords};
    }
}