#include <exception>
#include <stdexcept>
#include "util/WebGPUShaderModuleUtil.hpp"
#include "bns_types.hpp"

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
        if (module == nullptr)
        {
            std::string msg = "WebGPUShaderModuleUtil::Create: Failed to create shader module!";
            LOG(msg);
            BREAKPOINT();
            throw std::runtime_error(msg.c_str());
        }

        return module;
    }

    void WebGPUShaderModuleUtil::Dispose(WGPUShaderModule shaderModule)
    {
        wgpuShaderModuleRelease(shaderModule);
    }
}