#include "renderer/common/MetalRenderPipelineUtil.hpp"

namespace bns
{
     MTL::RenderPipelineDescriptor *MetalRenderPipelineUtil::CreatePipelineDescriptor(
        MTL::Function *pVertexFn,
        MTL::Function *pFragFn,
        MTL::PixelFormat pixelFormat)
    {

        MTL::RenderPipelineDescriptor *pDesc = MTL::RenderPipelineDescriptor::alloc()->init();
        pDesc->setVertexFunction(pVertexFn);
        pDesc->setFragmentFunction(pFragFn);
        pDesc->colorAttachments()->object(0)->setPixelFormat(pixelFormat); // by default MTL::PixelFormat::PixelFormatBGRA8Unorm_sRGB
        return pDesc;
    }
}