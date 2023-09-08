#include "loaders/BitmapSpriteFontLoader.hpp"
#include "loaders/ImageLoader.hpp"
#include "tinyxml2/tinyxml2.h"
#include "Framework.hpp"
#include "textures/metal/MetalTexture2D.hpp"

namespace bns
{
    BitmapSpriteFontLoader::BitmapSpriteFontLoader(const Framework &framework)
        : m_framework(framework)
    {
    }

    SpriteFont *BitmapSpriteFontLoader::LoadSnowBImpl(const std::string &fntPath, const std::string &imagePath)
    {
        ImageData *imageData = m_framework.GetImageLoader().LoadImage(imagePath);

#ifdef USE_METAL
        // TODO: texture factory
        Texture2D *texture = new MetalTexture2D(m_framework, imageData);
        texture->Initialize();
#else
        // TODO: webpgu
        Texture2D *texture = nullptr;
#endif
        std::string root = m_framework.GetDirectory().Root();
        tinyxml2::XMLDocument doc;
        doc.LoadFile(fntPath.c_str());

        tinyxml2::XMLElement *commonElement = doc.FirstChildElement("font")
                                                  ->FirstChildElement("common");

        i32 lineHeight = commonElement->IntAttribute("lineHeight");

        SpriteFont *font = new SpriteFont(texture);

        tinyxml2::XMLElement *charElement = doc.FirstChildElement("font")
                                                ->FirstChildElement("chars")
                                                ->FirstChildElement("char");
        while (charElement != nullptr)
        {
            i32 c = charElement->IntAttribute("id");
            i32 x = charElement->IntAttribute("x");
            i32 y = charElement->IntAttribute("y");
            i32 width = charElement->IntAttribute("width");
            i32 height = charElement->IntAttribute("height");
            i32 xoffset = charElement->IntAttribute("xoffset");
            i32 yoffset = charElement->IntAttribute("yoffset");
            i32 xadvance = charElement->IntAttribute("xadvance");

            Vec2i size = {width, height};
            Vec2i offset = {xoffset, yoffset};
            i32 advance = xadvance;

            // normalize
            f32 x1 = (f32)x / (f32)imageData->Width;
            f32 y1 = (f32)y / (f32)imageData->Height;
            f32 x2 = (f32)(x + width) / (f32)imageData->Width;
            f32 y2 = (f32)(y + height) / (f32)imageData->Height;

            Quad textureCoords;
            textureCoords.TopLeft = {x1, y1};
            textureCoords.TopRight = {x2, y1};
            textureCoords.BottomLeft = {x1, y2};
            textureCoords.BottomRight = {x2, y2};

            font->CreateChar(static_cast<char>(c), size, offset, advance, textureCoords);

            charElement = charElement->NextSiblingElement("char");
        }

        return font;
    }
}
