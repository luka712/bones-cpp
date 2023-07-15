#include "renderer/common/WebGPURenderPipelineUtil.hpp"

namespace bns
{
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

        WGPURenderPipelineDescriptor descriptor = {};

        // Other state
        descriptor.layout = nullptr;
        descriptor.depthStencil = nullptr;

        descriptor.vertex.module = vertexState.module;
        descriptor.vertex.entryPoint = "vs_main";
        descriptor.vertex.bufferCount = 0;
        descriptor.vertex.buffers = nullptr;

        descriptor.multisample.count = 1;
        descriptor.multisample.mask = 0xFFFFFFFF;
        descriptor.multisample.alphaToCoverageEnabled = false;

        descriptor.primitive.frontFace = WGPUFrontFace_CCW;
        descriptor.primitive.cullMode = WGPUCullMode_None;
        descriptor.primitive.topology = WGPUPrimitiveTopology_TriangleList;
        descriptor.primitive.stripIndexFormat = WGPUIndexFormat_Undefined;

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