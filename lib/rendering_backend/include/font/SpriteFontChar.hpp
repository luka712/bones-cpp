#ifndef BNS_SPRITE_FONT_CHAR_H

#define BNS_SPRITE_FONT_CHAR_H

#include "math/bns_vec2.hpp"
#include "math/bns_quad.hpp"

namespace bns 
{
    struct SpriteFontChar final
    {
        /**
         * @brief The size of the character.
         */
        Vec2i Size;

        /**
         * @brief The offset of the character.
        */
        Vec2i Offset;

        /**
         * @brief The advance of the character.
         */
        i32 Advance;

        /**
         * @brief The texture coordinates of the character.
         */
        Quad TextureCoords;
    };
}

#endif 