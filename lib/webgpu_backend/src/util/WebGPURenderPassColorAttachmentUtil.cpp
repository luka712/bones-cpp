#include "util/WebGPURenderPassColorAttachmentUtil.hpp"

namespace bns
{
    WGPURenderPassColorAttachment WebGPURenderPassColorAttachmentUtil::Create(const WGPUTextureView& view, Color clearColor)
    {
        WGPUColor wgpuClearColor = {
            clearColor.R,
            clearColor.G,
            clearColor.B,
            clearColor.A
        };

        WGPURenderPassColorAttachment colorAttachment = {};
        colorAttachment.view = view;
        colorAttachment.resolveTarget = nullptr;
        colorAttachment.clearValue = wgpuClearColor;
        colorAttachment.loadOp = WGPULoadOp_Clear;
        colorAttachment.storeOp = WGPUStoreOp_Store;

        return colorAttachment;
    }
} // namespace bns