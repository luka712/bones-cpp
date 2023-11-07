#ifndef BNS_WGPU_BLEND_STATE_UTIL_HPP

#define BNS_WGPU_BLEND_STATE_UTIL_HPP

#include <webgpu/webgpu.h>
#include "Types.hpp"

namespace bns
{
    struct WebGPUBlendStateUtil final
    {
        /**
         * @brief Set the default values for the blend state.
         * @param state The blend state.
         * 
         * By default the blend state is set to:
         * {
         *   .color = {
         *      .srcFactor = WGPUBlendFactor_One,
         *      .dstFactor = WGPUBlendFactor_Zero,
         *      .operation = WGPUBlendOperation_Add
         * },
         *   .alpha = {
         *      .srcFactor = WGPUBlendFactor_One,
         *      .dstFactor = WGPUBlendFactor_Zero,
         *      .operation = WGPUBlendOperation_Add
         * },
         */
        static void SetDefault(WGPUBlendState& state);

        /**
         * @brief Create a blend state.
         * @return The blend state.
         * 
         * By default the blend state is set to:
         * {
         *   .color = {
         *      .srcFactor = WGPUBlendFactor_One,
         *      .dstFactor = WGPUBlendFactor_Zero,
         *      .operation = WGPUBlendOperation_Add
         * },
         *   .alpha = {
         *      .srcFactor = WGPUBlendFactor_One,
         *      .dstFactor = WGPUBlendFactor_Zero,
         *      .operation = WGPUBlendOperation_Add
         * },
        */
        static WGPUBlendState Create();
    };
}

#endif