#ifndef BNS_WEBGPU_RENDER_PASS_COLOR_ATTACHMENT_UTIL_HPP

#define BNS_WEBGPU_RENDER_PASS_COLOR_ATTACHMENT_UTIL_HPP

#include <webgpu/webgpu.h>
#include "bns_color.hpp"

namespace bns
{
    class WebGPURenderPassColorAttachmentUtil final
    {
    public:
        /**
         * @brief Create a color attachment with a texture view.
        */
        static WGPURenderPassColorAttachment Create(const WGPUTextureView& view, Color clearColor = Color::Black());
    };
} // namespace bns

#endif // !BNS_WEBGPU_RENDER_PASS_COLOR_ATTACHMENT_UTIL_HPP