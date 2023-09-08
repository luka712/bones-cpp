#ifndef BNS_BITMAP_SPRITE_FONT_LOADER_HPP

#define BNS_BITMAP_SPRITE_FONT_LOADER_HPP

#include <string>
#include "font/SpriteFont.hpp"

namespace bns
{
    class Framework;

    /**
     * @brief A class to load a bitmap font from various implementations.
     * Supported: 
     * - https://snowb.org/
     */
    class BitmapSpriteFontLoader final
    {
    public:
        BitmapSpriteFontLoader(const Framework &framework);

        /**
         * @brief Load a font from a .fnt or .xml file. Implementation of https://snowb.org/ type of font.
         * @param path The path to the font file.
         * @param imagePath The path to the image file.
         */
        SpriteFont *LoadSnowBImpl(const std::string &fntPath, const std::string &imagePath);

    private:
        const Framework &m_framework;
    };
}

#endif