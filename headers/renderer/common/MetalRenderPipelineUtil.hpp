#ifndef BNS_METAL_RENDER_PIPELINE_UTIL_HPP

#define BNS_METAL_RENDER_PIPELINE_UTIL_HPP

#include <Metal/Metal.hpp>

namespace bns
{
    class MetalRenderPipelineUtil final
    {
    public:
        /**
         * @brief Create a new render pipeline descriptor.
         * The render pipeline descriptor is used to describe the render pipeline.
         * @param pVertexFn The vertex function to use.
         * @param pFragFn The fragment function to use.
         * @param pixelFormat The pixel format to use. Default is MTL::PixelFormat::PixelFormatBGRA8Unorm_sRGB.
         * @return MTL::RenderPipelineDescriptor * The new render pipeline descriptor.
         */
        static MTL::RenderPipelineDescriptor *CreatePipelineDescriptor(
            MTL::Function *pVertexFn,
            MTL::Function *pFragFn,
            MTL::PixelFormat pixelFormat = MTL::PixelFormat::PixelFormatBGRA8Unorm_sRGB);
    };
}

#endif // BNS_METAL_RENDER_PIPELINE_UTIL_HPP