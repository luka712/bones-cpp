#include "textures/TextureManagerImpl.hpp"
#include "Framework.hpp"

#if __APPLE__ && USE_METAL
#include "renderer/MetalRenderer.hpp"
#include "texture/MetalTexture2D.hpp"
#else
#include "texture/WebGPUTexture2D.hpp"
#endif

namespace bns
{
    TextureManagerImpl::TextureManagerImpl(Framework &framework)
        : TextureManager(framework.GetImageLoader()), m_framework(framework)
    {
    }

    Texture2D *TextureManagerImpl::CreateBackendImplTexture(ImageData *imageData, i32 textureUsageFlags, TextureFormat format)
    {
#if __APPLE__ && USE_METAL
        MetalRenderer* renderer = static_cast<MetalRenderer*>(m_framework.GetRenderer());
        return new MetalTexture2D(renderer->GetDevice(), imageData, textureUsageFlags, format);
#else
        return new WebGPUTexture2D(m_framework.Context.WebGPUDevice, imageData, textureUsageFlags, format);
#endif
    }
}
