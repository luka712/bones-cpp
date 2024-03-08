#if USE_METAL

#ifndef BNS_METAL_RENDER_PIPELINE_STATE_UTIL_HPP

#define BNS_METAL_RENDER_PIPELINE_STATE_UTIL_HPP

#include "bns_metal.hpp"
#include <string>
#include <functional>

namespace bns
{
    /// @brief The Metal render pipeline state utility class.
    struct MetalRenderPipelineStateUtil
    {
        /// @brief Create a Metal render pipeline state.
        /// @param device The device.
        /// @param library The library.
        /// @param vertexFunction The vertex function. By default it is "main_vs".
        /// @param fragmentFunction The fragment function. By default it is "main_fs".
        /// @param label The label. By default it is "".
        /// @return The render pipeline state.
        static MTL::RenderPipelineState* Create(
            MTL::Device *device,
            MTL::Library *library,
            std::string vertexFunction = "main_vs",
            std::string fragmentFunction = "main_fs",
            std::string label = "");

        /// @brief Destroy the Metal render pipeline state.
        /// @param pipeline The pipeline.
        static void Dispose(MTL::RenderPipelineState *pipeline);
    };
}

#endif

#endif