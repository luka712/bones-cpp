#include "util/wgpu/WebGPURenderPipelineDescriptorUtil.hpp"

namespace bns
{

    WGPURenderPipelineDescriptor WebGPURenderPipelineDescriptorUtil::Create(
        WGPUPipelineLayout pipelineLayout,
        WGPUVertexState vertexState,
        WGPUFragmentState fragmentState,
        WGPUDepthStencilState* depthStencilState,
        WGPUPrimitiveTopology primitiveTopology,
        WGPUCullMode cullMode,
        std::string label)
    {         
        WGPURenderPipelineDescriptor pipelineDesc;
        pipelineDesc.nextInChain = nullptr;
        pipelineDesc.label = label.c_str();
        pipelineDesc.layout = pipelineLayout;
        pipelineDesc.vertex = vertexState;
        pipelineDesc.fragment = &fragmentState;
        pipelineDesc.primitive.nextInChain = nullptr;
        pipelineDesc.primitive.topology = primitiveTopology;
        pipelineDesc.primitive.cullMode = cullMode;
        pipelineDesc.primitive.frontFace = WGPUFrontFace::WGPUFrontFace_CCW;
        pipelineDesc.primitive.stripIndexFormat = WGPUIndexFormat::WGPUIndexFormat_Undefined;
        pipelineDesc.multisample.nextInChain = nullptr;
        pipelineDesc.multisample.count = 1;
        pipelineDesc.multisample.mask = 0xFFFFFFFF;
        pipelineDesc.multisample.alphaToCoverageEnabled = false;
        
        if(depthStencilState != nullptr)
        {
            pipelineDesc.depthStencil = depthStencilState;
        }
        else 
        {
            pipelineDesc.depthStencil = nullptr;
        }

        return pipelineDesc;
    }

}
