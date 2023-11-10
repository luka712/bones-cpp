#include "textures/TextureManagerImpl.hpp"
#include "Framework.hpp"

#if __APPLE__ && USE_METAL
#include "renderer/MetalRenderer.hpp"
#include "texture/MetalTexture2D.hpp"
#else
#include "renderer/WebGPURenderer.hpp" 
#include "texture/WebGPUTexture2D.hpp"
#endif

namespace bns
{
    TextureManagerImpl::TextureManagerImpl(Renderer *renderer,ImageLoader *imageLoader)
        : TextureManager(imageLoader), m_renderer(renderer)
    {
    }

    Texture2D *TextureManagerImpl::CreateBackendImplTexture(ImageData *imageData, i32 textureUsageFlags, TextureFormat format)
    {
#if __APPLE__ && USE_METAL
        MetalRenderer* renderer = static_cast<MetalRenderer*>(m_renderer);
        return new MetalTexture2D(renderer->GetDevice(), imageData, textureUsageFlags, format);
#else
        WebGPURenderer* renderer = static_cast<WebGPURenderer*>(m_renderer);
        return new WebGPUTexture2D(renderer->GetDevice(), imageData, textureUsageFlags, format);
#endif
    }
}
