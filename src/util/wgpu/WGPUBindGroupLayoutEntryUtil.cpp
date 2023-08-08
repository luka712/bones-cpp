#include "util/wgpu/WGPUBindGroupLayoutEntryUtil.hpp"

namespace bns
{
    WGPUBindGroupLayoutEntry WGPUBindGroupLayoutEntryUtil::CreateBindGroupLayoutEntry(u32 binding, WGPUShaderStageFlags shaderStage)
    {
        WGPUBindGroupLayoutEntry bindGroupLayoutEntry = {};
        bindGroupLayoutEntry.nextInChain = nullptr;
        bindGroupLayoutEntry.binding = binding;
        bindGroupLayoutEntry.visibility = shaderStage;
        bindGroupLayoutEntry.buffer.type = WGPUBufferBindingType_Uniform;
        bindGroupLayoutEntry.sampler.type = WGPUSamplerBindingType_Undefined;            // sample is not used
        bindGroupLayoutEntry.buffer.type = WGPUBufferBindingType_Undefined;              // buffer is not used
        bindGroupLayoutEntry.texture.sampleType = WGPUTextureSampleType_Undefined;       // texture is not used
        bindGroupLayoutEntry.storageTexture.access = WGPUStorageTextureAccess_Undefined; // storage texture is not used

        return bindGroupLayoutEntry;
    }

    WGPUBindGroupLayoutEntry WGPUBindGroupLayoutEntryUtil::CreateBindGroupLayoutEntry(
        u32 binding,
        WGPUShaderStageFlags shaderStage,
        WGPUSamplerBindingLayout samplerBindingLayout)
    {
        WGPUBindGroupLayoutEntry entry = CreateBindGroupLayoutEntry(binding, shaderStage);
        entry.sampler = samplerBindingLayout;

        return entry;
    }

    WGPUBindGroupLayoutEntry WGPUBindGroupLayoutEntryUtil::CreateBindGroupLayoutEntry(
        u32 binding,
        WGPUShaderStageFlags shaderStage,
        WGPUTextureBindingLayout textureBindingLayout)
    {
        WGPUBindGroupLayoutEntry entry = CreateBindGroupLayoutEntry(binding, shaderStage);
        entry.texture = textureBindingLayout;

        return entry;
    }

    WGPUBindGroupLayoutEntry WGPUBindGroupLayoutEntryUtil::CreateBindGroupLayoutEntry(
        u32 binding,
        WGPUShaderStageFlags shaderStage,
        WGPUBufferBindingLayout bufferBindingLayout)
    {
        WGPUBindGroupLayoutEntry entry = CreateBindGroupLayoutEntry(binding, shaderStage);
        entry.buffer = bufferBindingLayout;

        return entry;
    }

    WGPUBindGroupLayoutEntry WGPUBindGroupLayoutEntryUtil::CreateBindGroupLayoutEntryForUniformBuffer(
        u32 binding,
        WGPUShaderStageFlags shaderStage)
    {
        WGPUBindGroupLayoutEntry entry = CreateBindGroupLayoutEntry(binding, shaderStage);
        entry.buffer.nextInChain = nullptr;
        entry.buffer.type = WGPUBufferBindingType_Uniform;
        entry.buffer.hasDynamicOffset = false;
        entry.buffer.minBindingSize = 0;

        return entry;
    }
}