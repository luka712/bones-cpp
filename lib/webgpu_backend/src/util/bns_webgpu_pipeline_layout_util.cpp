#if USE_WEBGPU

#include "util/bns_webgpu_pipeline_layout_util.hpp"
#include <stdexcept>
#include <string>
#include "bns_types.hpp"

namespace bns
{
    WGPUPipelineLayout WebGPUPipelineLayoutUtil::Create(WGPUDevice device, std::vector<WGPUBindGroupLayout> bindGroupLayouts)
    {
        WGPUPipelineLayoutDescriptor pipelineLayoutDescriptor = {};
        pipelineLayoutDescriptor.bindGroupLayoutCount = bindGroupLayouts.size();
        pipelineLayoutDescriptor.bindGroupLayouts = bindGroupLayouts.data();
        WGPUPipelineLayout pipelineLayout = wgpuDeviceCreatePipelineLayout(device, &pipelineLayoutDescriptor);

        if (pipelineLayout == nullptr)
        {
            std::string msg = "WebGPUPipelineLayoutUtil::Create: Failed to create pipeline layout.";
            LOG(msg);
            BREAKPOINT();
            throw std::runtime_error(msg.c_str());
        }

        return pipelineLayout;
    }

    void WebGPUPipelineLayoutUtil::Dispose(WGPUPipelineLayout pipelineLayout)
    {
        wgpuPipelineLayoutRelease(pipelineLayout);
    }
}

#endif