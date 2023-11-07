#include "util/WebGPUBindGroupEntryUtil.hpp"

namespace bns
{

    WGPUBindGroupEntry WebGPUBindGroupEntryUtil::Create()
    {
        WGPUBindGroupEntry bindGroupEntry = {};
        bindGroupEntry.binding = 0;
        bindGroupEntry.buffer = nullptr;
        bindGroupEntry.offset = 0;
        bindGroupEntry.size = 0;
        bindGroupEntry.sampler = nullptr;
        bindGroupEntry.textureView = nullptr;
        return bindGroupEntry;
    }

    WGPUBindGroupEntry WebGPUBindGroupEntryUtil::Create(u32 binding, WGPUBuffer buffer, size_t byteSize)
    {
        WGPUBindGroupEntry bindGroupEntry = Create();
        bindGroupEntry.size = byteSize;
        bindGroupEntry.binding = binding;
        bindGroupEntry.buffer = buffer;

        return bindGroupEntry;
    }

    WGPUBindGroupEntry WebGPUBindGroupEntryUtil::Create(u32 binding, WGPUSampler textureSampler)
    {
        WGPUBindGroupEntry bindGroupEntry = Create();
        bindGroupEntry.binding = binding;
        bindGroupEntry.sampler = textureSampler;

        return bindGroupEntry;
    }

    WGPUBindGroupEntry WebGPUBindGroupEntryUtil::Create(u32 binding, WGPUTextureView textureView)
    {
        WGPUBindGroupEntry bindGroupEntry = Create();
        bindGroupEntry.binding = binding;
        bindGroupEntry.textureView = textureView;

        return bindGroupEntry;
    }

} // namespace bns