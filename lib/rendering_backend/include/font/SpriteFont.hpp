#ifndef BNS_SPRITE_FONT_H

#define BNS_SPRITE_FONT_H

#include <string>
#include <map>
#include "font/SpriteFontChar.hpp"
#include "texture/bns_texture2d.hpp"
#include <stdexcept>

namespace bns
{
    class SpriteFont
    {
    public:
        /**
         * @brief Construct a new SpriteFont object
         */
        SpriteFont(Texture2D *texture);

        /**
         * @brief Create a character.
         * @param c The character to create.
         * @param size The size of the character.
         * @param offset The offset of the character.
         * @param advance The advance of the character.
         * @param textureCoords The texture coordinates of the character.
         */
        void CreateChar(char c, Vec2i size, Vec2i offset, i32 advance, Quad textureCoords);

        /**
         * @brief Get the Char object
         * @param c The character to get.
         */
        inline const SpriteFontChar &GetChar(char c) const
        {
            if (m_chars.find(c) == m_chars.end())
                throw std::runtime_error("Character not found in font: " + std::to_string(c) + ".");

            return m_chars.at(c);
        }

        /**
         * @brief Get the Texture object
         */
        inline Texture2D *GetTexture() const
        {
            return m_texture;
        }

    private:
        std::map<char, SpriteFontChar> m_chars;
        Texture2D *m_texture;
    };
}

#endif // !BNS_SPRITE_FONT_H