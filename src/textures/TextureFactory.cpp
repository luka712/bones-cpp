#include "textures/TextureFactory.hpp"

#if __APPLE__ && USE_METAL
#include "textures/metal/MetalTexture2D.hpp"
#else
#include "textures/wgpu/WebGPUTexture2D.hpp"
#endif

namespace bns
{
    TextureFactory::TextureFactory(const Framework &framework)
        : m_framework(framework)
    {
    }

    Texture2D *TextureFactory::CreateTexture(ImageData *imageData)
    {
        Texture2D *texture = nullptr;
#if __APPLE__ && USE_METAL
        texture = MetalTexture2D(m_framework, imageData);
#else
        texture = new WebGPUTexture2D(m_framework, imageData);
#endif
        texture->Initialize();
        return texture;
    }
}