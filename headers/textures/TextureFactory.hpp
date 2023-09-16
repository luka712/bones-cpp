#ifndef BNS_TEXTURE_FACTORY_HPP

#define BNS_TEXTURE_FACTORY_HPP

#include "textures/Texture2D.hpp"
#include "loaders/ImageLoader.hpp"

namespace bns
{
    class Framework;

    class TextureFactory final 
    {
    private:
        const Framework &m_framework;

    public:
        /**
         * @brief Construct a new TextureFactory object
        */
        TextureFactory(const Framework &framework);

        /**
         * @brief Create a texture.
         * @param imageData The image data.
         * @return Texture2D* The texture.
         */
        Texture2D *CreateTexture(ImageData *imageData);
    };
}

#endif // !BNS_TEXTURE_FACTORY_HPP