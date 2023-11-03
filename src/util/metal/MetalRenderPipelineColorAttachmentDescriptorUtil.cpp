#ifdef __APPLE__

#include "util/metal/MetalRenderPipelineColorAttachmentDescriptorUtil.hpp"

namespace bns
{
    void MetalRenderPipelineColorAttachmentDescriptorUtil::SetDefault(MTL::RenderPipelineColorAttachmentDescriptor &colorAttachment)
    {
        colorAttachment.setPixelFormat(MTL::PixelFormat::PixelFormatBGRA8Unorm);

        colorAttachment.setBlendingEnabled(true);

        colorAttachment.setRgbBlendOperation(MTL::BlendOperationAdd);
        colorAttachment.setSourceRGBBlendFactor(MTL::BlendFactorSourceAlpha);
        colorAttachment.setDestinationRGBBlendFactor(MTL::BlendFactorOneMinusSourceAlpha);

        colorAttachment.setAlphaBlendOperation(MTL::BlendOperationAdd);
        colorAttachment.setSourceAlphaBlendFactor(MTL::BlendFactorSourceAlpha);
        colorAttachment.setDestinationAlphaBlendFactor(MTL::BlendFactorOneMinusSourceAlpha);
    }
}

#endif // __APPLE__