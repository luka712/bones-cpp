#include "renderer/common/WebGPURenderPipelineUtil.hpp"

namespace bns
{
    WGPUFragmentState WebGPURenderPipelineUtil::CreateFragmentState(WGPUShaderModule shaderModule)
    {
        // Fragment state
        WGPUBlendState blend = {};
        blend.color.operation = WGPUBlendOperation_Add;
        blend.color.srcFactor = WGPUBlendFactor_One;
        blend.color.dstFactor = WGPUBlendFactor_One;
        blend.alpha.operation = WGPUBlendOperation_Add;
        blend.alpha.srcFactor = WGPUBlendFactor_One;
        blend.alpha.dstFactor = WGPUBlendFactor_One;

        WGPUColorTargetState colorTargetState;
        colorTargetState.nextInChain = nullptr;
        colorTargetState.format = WGPUTextureFormat::WGPUTextureFormat_BGRA8Unorm;
        colorTargetState.blend = &blend;
        colorTargetState.writeMask = WGPUColorWriteMask::WGPUColorWriteMask_All;

        WGPUFragmentState fragmentState;
        fragmentState.nextInChain = nullptr;
        fragmentState.module = shaderModule;
        fragmentState.entryPoint = "fs_main";
        fragmentState.targetCount = 1;
        fragmentState.targets = &colorTargetState;
        return fragmentState;
    }

    WGPURenderPipelineDescriptor WebGPURenderPipelineUtil::CreatePipelineDescriptor(
        WGPUPipelineLayout pipelineLayout,
        WGPUVertexState vertexState,
        WGPUFragmentState fragmentState,
        WGPUPrimitiveTopology primitiveTopology,
        WGPUCullMode cullMode,
        std::string label)
    {
        WGPUDepthStencilState depthStencilState;
        depthStencilState.depthWriteEnabled = true;
        depthStencilState.depthCompare = WGPUCompareFunction::WGPUCompareFunction_LessEqual;
        depthStencilState.format = WGPUTextureFormat::WGPUTextureFormat_Depth24PlusStencil8;

        WGPURenderPipelineDescriptor pipelineDesc;
        pipelineDesc.nextInChain = nullptr;
        pipelineDesc.label = label.c_str();
        pipelineDesc.layout = pipelineLayout;
        pipelineDesc.depthStencil = &depthStencilState;
        pipelineDesc.vertex = vertexState;
        pipelineDesc.fragment = &fragmentState;
        pipelineDesc.primitive.topology = primitiveTopology;
        pipelineDesc.primitive.cullMode = cullMode;
        pipelineDesc.primitive.frontFace = WGPUFrontFace::WGPUFrontFace_CCW;
        pipelineDesc.primitive.stripIndexFormat = WGPUIndexFormat::WGPUIndexFormat_Undefined;
        pipelineDesc.multisample.count = 1;
        pipelineDesc.multisample.mask = 0xFFFFFFFF;
        pipelineDesc.multisample.alphaToCoverageEnabled = false;

        return pipelineDesc;
    }

    WGPUShaderModule WebGPURenderPipelineUtil::CreateShaderModule(WGPUDevice device, std::string source, std::string label)
    {
        WGPUShaderModuleWGSLDescriptor wgslDesc;
        wgslDesc.chain.next = nullptr;
        wgslDesc.chain.sType = WGPUSType::WGPUSType_ShaderModuleWGSLDescriptor;
        wgslDesc.code = source.c_str();
        WGPUShaderModuleDescriptor descriptor;
        descriptor.nextInChain = reinterpret_cast<WGPUChainedStruct *>(&wgslDesc);
        descriptor.label = label.c_str();

        return wgpuDeviceCreateShaderModule(device, &descriptor);
    }

}