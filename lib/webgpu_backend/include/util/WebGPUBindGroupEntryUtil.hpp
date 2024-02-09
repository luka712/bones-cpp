#ifndef BNS_WGPU_BIND_GROUP_ENTRY_UTIL_HPP

#define BNS_WGPU_BIND_GROUP_ENTRY_UTIL_HPP

#include <webgpu/webgpu.h>
#include "bns_types.hpp"

namespace bns
{
    struct WebGPUBindGroupEntryUtil final
    {
        /**
         * @brief Create a bind group entry
         *
         */
        static WGPUBindGroupEntry Create();

        /**
         * @brief Create a bind group entry for a buffer.
         * @param binding The binding number of the bind group entry.
         * @param buffer The buffer of the bind group entry.
         * @param byteSize The size of the buffer in bytes.
         * @return The bind group entry.
         */
        static WGPUBindGroupEntry Create(u32 binding, WGPUBuffer buffer, size_t byteSize);

        /**
         * @brief Create a bind group entry for a texture sampler.
         * @param binding The binding number of the bind group entry.
         * @param textureSampler The texture sampler of the bind group entry.
         * @return The bind group entry.
         */
        static WGPUBindGroupEntry Create(u32 binding, WGPUSampler textureSampler);

        /**
         * @brief Create a bind group entry for a texture view.
         * @param binding The binding number of the bind group entry.
         * @param textureView The texture view of the bind group entry.
         * @return The bind group entry.
         */
        static WGPUBindGroupEntry Create(u32 binding, WGPUTextureView textureView);
    };
}

#endif