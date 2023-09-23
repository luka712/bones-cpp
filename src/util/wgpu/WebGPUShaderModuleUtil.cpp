#include "util/wgpu/WebGPUShaderModuleUtil.hpp"

namespace bns
{
    WGPUShaderModule WebGPUShaderModuleUtil::Create(WGPUDevice device, const std::string &shaderCode, std::string label)
    {
        WGPUShaderModuleWGSLDescriptor wgslDesc;
        wgslDesc.chain.next = nullptr;
        wgslDesc.chain.sType = WGPUSType::WGPUSType_ShaderModuleWGSLDescriptor;
        wgslDesc.code = shaderCode.c_str();
        WGPUShaderModuleDescriptor descriptor;
        descriptor.nextInChain = reinterpret_cast<WGPUChainedStruct *>(&wgslDesc);
        descriptor.label = label.c_str();

        return wgpuDeviceCreateShaderModule(device, &descriptor);
    }
}