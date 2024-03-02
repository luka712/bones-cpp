#if USE_WEBGPU

#ifndef BNS_WEBGPU_BIND_GROUP_UTIL_HPP

#define BNS_WEBGPU_BIND_GROUP_UTIL_HPP

#include "bns_types.hpp"
#include "bns_webgpu.hpp"
#include <vector>
#include <string>

namespace bns
{
    /// @brief The bind group entry. Translates to actual bind group entry in WebGPU.
    struct WebGPUBindGroupEntry
    {
        /// @brief The binding.
        u32 Binding;

        /// @brief The offset.
        size_t Offset;

        /// @brief The size.
        size_t Size;

        /// @brief The buffer.
        WGPUBuffer Buffer;

        /// @brief The sampler.
        WGPUSampler Sampler;

        /// @brief The texture view.
        WGPUTextureView TextureView;

        /// @brief The constructor.
        WebGPUBindGroupEntry();

        /// @brief Translates to actual bind group entry in WebGPU.
        /// @return The actual bind group entry in WebGPU.
        WGPUBindGroupEntry Translate();
    };

    /// @brief The bind group utility.
    struct WebGPUBindGroupUtil
    {
        /// @brief Create a bind group.
        /// @param device The device.
        /// @param layout The layout.
        /// @param entries The entries.
        /// @param label The label.
        /// @return The bind group.
        static WGPUBindGroup Create(
            WGPUDevice device,
            WGPUBindGroupLayout layout,
            std::vector<WebGPUBindGroupEntry> entries,
            std::string label = "");
    };
}

#endif

#endif