#ifndef BNS_METAL_COLOR_ATTACHMENT_UTIL_HPP

#define BNS_METAL_COLOR_ATTACHMENT_UTIL_HPP

#include "Metal.hpp"

namespace bns
{
    /// @brief The Metal render pipeline color attachment descriptor util.
    class MetalRenderPipelineColorAttachmentDescriptorUtil final 
    {
    public:
        /// @brief Sets the default values for the color attachment descriptor.
        /// @param descriptor The reference to the color attachment descriptor to set the default values for.
        /// Defaults:
        /// pixelFormat: PixelFormatBGRA8Unorm
        /// blendingEnabled: true
        /// rgbBlendOperation: BlendOperationAdd
        /// sourceRGBBlendFactor: BlendFactorSourceAlpha
        /// destinationRGBBlendFactor: BlendFactorOneMinusSourceAlpha
        /// alphaBlendOperation: BlendOperationAdd
        /// sourceAlphaBlendFactor: BlendFactorSourceAlpha
        static void SetDefault(MTL::RenderPipelineColorAttachmentDescriptor &colorAttachment);
    };
}

#endif