#if USE_WEBGPU

#include "util/bns_webgpu_bind_group_layout_util.hpp"
#include <string>
#include <stdexcept>

namespace bns
{
	WebGPUBindGroupLayoutEntry::WebGPUBindGroupLayoutEntry()
	{
		Binding = 0;
		// Set to unfedined value by default.
		BufferBindingLayout.type = WGPUBufferBindingType_Undefined;
		SamplerBindingLayout.type = WGPUSamplerBindingType_Undefined;
		TextureBindingLayout.sampleType = WGPUTextureSampleType_Undefined;
		StorageTextureBindingLayout.access = WGPUStorageTextureAccess_Undefined;
	}

	WebGPUBindGroupLayoutEntry::~WebGPUBindGroupLayoutEntry()
	{
		// Set to undefined.
		BufferBindingLayout.type = WGPUBufferBindingType_Undefined;
		SamplerBindingLayout.type = WGPUSamplerBindingType_Undefined;
		TextureBindingLayout.sampleType = WGPUTextureSampleType_Undefined;
		StorageTextureBindingLayout.access = WGPUStorageTextureAccess_Undefined;
	}

	WebGPUBindGroupLayoutEntry WebGPUBindGroupLayoutEntry::CreateUniformBufferLayoutEntry(u32 binding, ShaderType visibility)
	{
		WebGPUBindGroupLayoutEntry entry = {};
		entry.Binding = binding;
		entry.Visibility = visibility;
		entry.BufferBindingLayout = {};
		entry.BufferBindingLayout.nextInChain = nullptr;
		entry.BufferBindingLayout.hasDynamicOffset = false;
		entry.BufferBindingLayout.minBindingSize = 0;
		entry.BufferBindingLayout.type = WGPUBufferBindingType_Uniform;
		return entry;
	}

	WebGPUBindGroupLayoutEntry WebGPUBindGroupLayoutEntry::CreateTextureLayoutEntry(u32 binding, ShaderType visibility)
	{
		WebGPUBindGroupLayoutEntry entry = {};
		entry.Binding = binding;
		entry.Visibility = visibility;
		entry.TextureBindingLayout = {};
		entry.TextureBindingLayout.nextInChain = nullptr;
		entry.TextureBindingLayout.sampleType = WGPUTextureSampleType_Float;
		entry.TextureBindingLayout.viewDimension = WGPUTextureViewDimension_2D;
		entry.TextureBindingLayout.multisampled = false;
		return entry;
	}

	WebGPUBindGroupLayoutEntry WebGPUBindGroupLayoutEntry::CreateSamplerLayoutEntry(u32 binding, ShaderType visibility)
	{
		WebGPUBindGroupLayoutEntry entry = {};
		entry.Binding = binding;
		entry.Visibility = visibility;
		entry.SamplerBindingLayout = {};
		entry.SamplerBindingLayout.nextInChain = nullptr;
		entry.SamplerBindingLayout.type = WGPUSamplerBindingType_Filtering;
		return entry;
	}

	u32 WebGPUBindGroupLayoutUtil::MapShaderStage(ShaderType shaderType)
	{
		switch (shaderType)
		{
		case ShaderType::Vertex:
			return WGPUShaderStage_Vertex;
		case ShaderType::Fragment:
			return WGPUShaderStage_Fragment;
		case ShaderType::Compute:
			return WGPUShaderStage_Compute;
		}

		std::string msg = "WebGPUBindGroupLayoutUtil::MapShaderStage: Unsupported shader stage." LOG(msg);
		BREAKPOINT();
		throw std::runtime_error(msg.c_str());
	}

	WGPUBindGroupLayout WebGPUBindGroupLayoutUtil::Create(WGPUDevice device, std::vector<WebGPUBindGroupLayoutEntry>& bindGroupEntries, std::string label)
	{
		std::vector<WGPUBindGroupLayoutEntry> entries = std::vector<WGPUBindGroupLayoutEntry>(bindGroupEntries.size());

		size_t i = 0;
		for (const WebGPUBindGroupLayoutEntry& entry : bindGroupEntries)
		{
			// copy from our custom class to the WGPUBindGroupLayoutEntry.
			WGPUBindGroupLayoutEntry& wgpuEntry = entries[i];
			wgpuEntry.binding = entry.Binding;
			wgpuEntry.visibility = MapShaderStage(entry.Visibility);
			wgpuEntry.buffer = entry.BufferBindingLayout;
			wgpuEntry.texture = entry.TextureBindingLayout;
			wgpuEntry.sampler = entry.SamplerBindingLayout;
			wgpuEntry.storageTexture = entry.StorageTextureBindingLayout;

			i++;
		}

		WGPUBindGroupLayoutDescriptor bindGroupLayoutDesc;
		bindGroupLayoutDesc.nextInChain = nullptr;
		bindGroupLayoutDesc.entries = entries.data();
		bindGroupLayoutDesc.entryCount = bindGroupEntries.size();
		bindGroupLayoutDesc.label = label.c_str();

		WGPUBindGroupLayout bindGroupLayout = wgpuDeviceCreateBindGroupLayout(device, &bindGroupLayoutDesc);
		if (bindGroupLayout == nullptr)
		{
			std::string msg = "WebGPUBindGroupLayoutUtil::Create: Unable to create WGPUBindGroupLayout.";
			LOG(msg);
			BREAKPOINT();
			throw std::runtime_error(msg.c_str());
		}

		return bindGroupLayout;
	}

	void WebGPUBindGroupLayoutUtil::Dispose(WGPUBindGroupLayout bindGroupLayout)
	{
		wgpuBindGroupLayoutRelease(bindGroupLayout);
	}
}

#endif