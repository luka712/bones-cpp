#ifdef __APPLE__

#ifndef BNS_METAL_RENDER_PIPELINE_UTIL_HPP

#define BNS_METAL_RENDER_PIPELINE_UTIL_HPP

#include "BnsMetal.hpp"

namespace bns
{
    class MetalRenderPipelineDescriptorUtil final
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
        static MTL::RenderPipelineDescriptor *Create(
            MTL::Function *pVertexFn,
            MTL::Function *pFragFn,
            MTL::PixelFormat pixelFormat = MTL::PixelFormat::PixelFormatBGRA8Unorm_sRGB);
    };
}

#endif // BNS_METAL_RENDER_PIPELINE_UTIL_HPP

#endif // __APPLE__