#if USE_WEBGPU

#include "util/bns_webgpu_bind_group_util.hpp"
#include <stdexcept>

namespace bns
{
    WebGPUBindGroupEntry::WebGPUBindGroupEntry()
    {
        Binding = 0;
        Offset = 0;
        Size = 0;
        Buffer = nullptr;
        Sampler = nullptr;
        TextureView = nullptr;
    }

    WGPUBindGroupEntry WebGPUBindGroupEntry::Translate()
    {
        WGPUBindGroupEntry entry = {};
        entry.nextInChain = nullptr;
        entry.binding = Binding;
        entry.offset = Offset;
        entry.size = Size;
        entry.buffer = Buffer;
        entry.sampler = Sampler;
        entry.textureView = TextureView;
        return entry;
    }

    WGPUBindGroup WebGPUBindGroupUtil::Create(
        WGPUDevice device,
        WGPUBindGroupLayout layout,
        std::vector<WebGPUBindGroupEntry> entries,
        std::string label)
    {
        // Create entries.
        std::vector<WGPUBindGroupEntry> bindGroupEntriesInWGPU;
        for (WebGPUBindGroupEntry &entry : entries)
        {
            bindGroupEntriesInWGPU.push_back(entry.Translate());
        }

        WGPUBindGroupDescriptor descriptor = {};
        descriptor.nextInChain = nullptr;
        descriptor.layout = layout;
        descriptor.entryCount = bindGroupEntriesInWGPU.size();
        descriptor.entries = bindGroupEntriesInWGPU.data();
        if (label != "")
        {
            descriptor.label = label.c_str();
        }
        WGPUBindGroup bindGroup = wgpuDeviceCreateBindGroup(device, &descriptor);

        if (bindGroup == nullptr)
        {
            std::string msg = "WebGPUBindGroupUtil::Create: Failed to create bind group.";
            LOG(msg);
            BREAKPOINT();
            throw std::runtime_error(msg);
        }

        return bindGroup;
    }
}

#endif // USE_WEBGPU
