#include "util/wgpu/WebGPUShaderModuleUtil.hpp"
#include <exception>

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

         WGPUShaderModule module = wgpuDeviceCreateShaderModule(device, &descriptor);
         if(module == nullptr)
         {
            throw std::runtime_error("Failed to create shader module!");
         }

         return module;
    }
}