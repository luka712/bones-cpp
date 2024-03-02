#ifndef BNS_WEBGPU_RENDER_PASS_DESCRIPTOR_UTIL_HPP

#define BNS_WEBGPU_RENDER_PASS_DESCRIPTOR_UTIL_HPP

#include <webgpu/webgpu.h>
#include "bns_color.hpp"

namespace bns
{
    class WebGPURenderPassDescriptorUtil final 
    {
    public:
        /**
         * @brief Create a render pass descriptor with 1 color attachment and no depth stencil attachment.
        */
        static WGPURenderPassDescriptor Create(const WGPURenderPassColorAttachment& colorAttachment);

        /**
         * @brief Create a render pass descriptor with 1 color attachment and 1 depth stencil attachment.
         * @param colorAttachment The color attachment to use.
         * @param depthStencilAttachment The depth stencil attachment to use.
         * @return WGPURenderPassDescriptor The render pass descriptor.
        */
        static WGPURenderPassDescriptor Create(
            const WGPURenderPassColorAttachment& colorAttachment, 
            const WGPURenderPassDepthStencilAttachment& depthStencilAttachment);
    };
} // namespace bns

#endif // !BNS_WEBGPU_RENDER_PASS_DESCRIPTOR_UTIL_HPP