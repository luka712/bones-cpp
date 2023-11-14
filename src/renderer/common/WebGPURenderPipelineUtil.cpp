#if USE_WEBGPU

#include "renderer/common/WebGPURenderPipelineUtil.hpp"

namespace bns
{
    WGPURenderPipelineDescriptor WebGPURenderPipelineUtil::Create(
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
}

#endif 