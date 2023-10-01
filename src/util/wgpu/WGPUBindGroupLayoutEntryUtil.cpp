#include "util/wgpu/WebGPUBindGroupLayoutEntryUtil.hpp"

namespace bns
{
    WGPUBindGroupLayoutEntry WebGPUBindGroupLayoutEntryUtil::CreateBindGroupLayoutEntry(u32 binding, WGPUShaderStageFlags shaderStage)
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

    WGPUBindGroupLayoutEntry WebGPUBindGroupLayoutEntryUtil::CreateBindGroupLayoutEntry(
        u32 binding,
        WGPUShaderStageFlags shaderStage,
        WGPUSamplerBindingLayout samplerBindingLayout)
    {
        WGPUBindGroupLayoutEntry entry = CreateBindGroupLayoutEntry(binding, shaderStage);
        entry.sampler = samplerBindingLayout;

        return entry;
    }

    WGPUBindGroupLayoutEntry WebGPUBindGroupLayoutEntryUtil::CreateBindGroupLayoutEntry(
        u32 binding,
        WGPUShaderStageFlags shaderStage,
        WGPUTextureBindingLayout textureBindingLayout)
    {
        WGPUBindGroupLayoutEntry entry = CreateBindGroupLayoutEntry(binding, shaderStage);
        entry.texture = textureBindingLayout;

        return entry;
    }

    WGPUBindGroupLayoutEntry WebGPUBindGroupLayoutEntryUtil::CreateBindGroupLayoutEntry(
        u32 binding,
        WGPUShaderStageFlags shaderStage,
        WGPUBufferBindingLayout bufferBindingLayout)
    {
        WGPUBindGroupLayoutEntry entry = CreateBindGroupLayoutEntry(binding, shaderStage);
        entry.buffer = bufferBindingLayout;

        return entry;
    }

    WGPUBindGroupLayoutEntry WebGPUBindGroupLayoutEntryUtil::CreateUniformBufferLayoutEntry(
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

    WGPUBindGroupLayoutEntry WebGPUBindGroupLayoutEntryUtil::CreateSamplerLayoutEntry(u32 binding, WGPUShaderStageFlags shaderStage)
    {
        WGPUSamplerBindingLayout samplerBindingLayout = {};
        samplerBindingLayout.type = WGPUSamplerBindingType_Filtering;

        WGPUBindGroupLayoutEntry bindGroupLayoutEntry = CreateBindGroupLayoutEntry(binding, shaderStage, samplerBindingLayout);

        return bindGroupLayoutEntry;
    }

    WGPUBindGroupLayoutEntry WebGPUBindGroupLayoutEntryUtil::CreateTextureLayoutEntry(u32 binding, WGPUShaderStageFlags shaderStage)
    {
        WGPUTextureBindingLayout textureBindingLayout = {};
        textureBindingLayout.sampleType = WGPUTextureSampleType_Float;
        textureBindingLayout.viewDimension = WGPUTextureViewDimension_2D;

        WGPUBindGroupLayoutEntry bindGroupLayoutEntry = CreateBindGroupLayoutEntry(binding, shaderStage, textureBindingLayout);

        return bindGroupLayoutEntry;
    }
}