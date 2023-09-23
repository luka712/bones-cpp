#include "util/wgpu/WebGPURenderPassDescriptorUtil.hpp"

namespace bns
{
    WGPURenderPassDescriptor WebGPURenderPassDescriptorUtil::Create(const WGPURenderPassColorAttachment& colorAttachment)
    {
        WGPURenderPassDescriptor renderPassDesc = {};
        renderPassDesc.colorAttachmentCount = 1;
        renderPassDesc.colorAttachments = &colorAttachment;
        renderPassDesc.depthStencilAttachment = nullptr;

        return renderPassDesc;
    }

 WGPURenderPassDescriptor WebGPURenderPassDescriptorUtil::Create(const WGPURenderPassColorAttachment& colorAttachment, 
 const WGPURenderPassDepthStencilAttachment& depthStencilAttachment)
    {
        WGPURenderPassDescriptor renderPassDesc = {};
        renderPassDesc.colorAttachmentCount = 1;
        renderPassDesc.colorAttachments = &colorAttachment;
        renderPassDesc.depthStencilAttachment = &depthStencilAttachment;

        return renderPassDesc;
    }

} // namespace bns
