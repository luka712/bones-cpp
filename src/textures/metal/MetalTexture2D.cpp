#include "textures/metal/MetalTexture2D.hpp"
#include "Framework.hpp"

namespace bns
{
    MetalTexture2D::MetalTexture2D(Framework &framework, ImageData *imageData)
        : Texture2D(imageData->Width, imageData->Height), m_framework(framework), m_imageData(imageData)
    {
    }

    void MetalTexture2D::Initialize()
    {
        MTL::Device *device = m_framework.Context.MetalDevice;

        NS::UInteger texWidth = m_imageData->Width;
        NS::UInteger texHeight = m_imageData->Height;

        MTL::TextureDescriptor *textureDescriptor = MTL::TextureDescriptor::alloc()->init();
        textureDescriptor->setTextureType(MTL::TextureType2D);
        textureDescriptor->setPixelFormat(MTL::PixelFormatRGBA8Unorm);
        textureDescriptor->setWidth(texWidth);
        textureDescriptor->setHeight(texHeight);
        textureDescriptor->setStorageMode(MTL::StorageModeManaged);
        textureDescriptor->setUsage(MTL::ResourceUsageSample | MTL::ResourceUsageRead);

        MTL::Texture *texture = device->newTexture(textureDescriptor);
        // textureDescriptor->release();

        MTL::Region region;
        region.origin = {0, 0, 0};
        region.size = {texWidth, texHeight, 1};

        // bytes per row
        NS::Integer bytesPerRow = 4 * m_imageData->Width;

        texture->replaceRegion(region, 0, m_imageData->Data, bytesPerRow);

        MTL::SamplerDescriptor *samplerDescriptor = MTL::SamplerDescriptor::alloc()->init();

        Sampler = device->newSamplerState(samplerDescriptor);
       //  samplerDescriptor->release();

        Texture = texture;
    }
}
