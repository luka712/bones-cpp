#if USE_WEBGPU

#include "util/bns_webgpu_render_pipeline_util.hpp"
#include <stdexcept>

namespace bns
{
    WGPUVertexStepMode WebGPURenderPipelineUtil::ResolveStepMode(VertexStepMode stepMode)
    {
        switch (stepMode)
        {
        case VertexStepMode::Vertex:
            return WGPUVertexStepMode_Vertex;
        case VertexStepMode::Instance:
            return WGPUVertexStepMode_Instance;
        }

        std::string msg = "WebGPURenderPipelineUtil::ResolveStepMode: Unknown step mode.";
        LOG(msg);
        BREAKPOINT();
        throw std::runtime_error(msg);
    }

    WGPUVertexFormat WebGPURenderPipelineUtil::ResolveVertexFormat(VertexFormat format)
    {
        switch (format)
        {
        case VertexFormat::Float32x1:
            return WGPUVertexFormat_Float32;
        case VertexFormat::Float32x2:
            return WGPUVertexFormat_Float32x2;
        case VertexFormat::Float32x3:
            return WGPUVertexFormat_Float32x3;
        case VertexFormat::Float32x4:
            return WGPUVertexFormat_Float32x4;
        }

        std::string msg = "WebGPURenderPipelineUtil::ResolveVertexFormat: Unknown vertex format.";
        LOG(msg);
        BREAKPOINT();
        throw std::runtime_error(msg);
    }

    WGPURenderPipeline WebGPURenderPipelineUtil::Create(
        WGPUDevice device,
        WGPUShaderModule shaderModule,
        WGPUPipelineLayout pipelineLayout,
        std::vector<BufferLayoutDescriptor> bufferLayoutDescriptors,
        std::string vertexEntryPoint,
        std::string fragmentEntryPoint,
        std::string label)
    {
        // VERTEX STATE
        // Buffer layouts
        WGPUVertexBufferLayout* vertexBufferLayouts = new WGPUVertexBufferLayout[bufferLayoutDescriptors.size()];
        u32 vertexBufferLayoutCount = bufferLayoutDescriptors.size();
        for (size_t i = 0; i < vertexBufferLayoutCount; i++)
        {
            BufferLayoutDescriptor bufferLayoutDescriptor = bufferLayoutDescriptors[i];
            vertexBufferLayouts[i].arrayStride = bufferLayoutDescriptor.Stride;
            vertexBufferLayouts[i].stepMode = ResolveStepMode(bufferLayoutDescriptor.Step);
            WGPUVertexAttribute* attributes = new WGPUVertexAttribute[bufferLayoutDescriptor.Attributes.size()];
            vertexBufferLayouts[i].attributeCount = bufferLayoutDescriptor.Attributes.size();
            vertexBufferLayouts[i].attributes = &attributes[0];

            for (size_t j = 0; j < bufferLayoutDescriptor.Attributes.size(); j++)
            {
                BufferLayoutAttributeDescriptor bufferLayoutAttributeDescriptor = bufferLayoutDescriptor.Attributes[j];
                attributes[j].format = ResolveVertexFormat(bufferLayoutAttributeDescriptor.Format);
                attributes[j].offset = bufferLayoutAttributeDescriptor.Offset;
                attributes[j].shaderLocation = bufferLayoutAttributeDescriptor.ShaderLocation;
            }
        }

        WGPUVertexState vertexState;
        vertexState.nextInChain = nullptr;
        vertexState.entryPoint = vertexEntryPoint.c_str();
        vertexState.module = shaderModule;
        vertexState.bufferCount = vertexBufferLayoutCount;
        vertexState.buffers = vertexBufferLayouts;
        vertexState.constantCount = 0;

        // FRAGMENT STATE
        // color target
        WGPUColorTargetState colorTargetState;
        colorTargetState.nextInChain = nullptr;
        colorTargetState.format = WGPUTextureFormat_BGRA8Unorm;
        colorTargetState.blend = nullptr;
        colorTargetState.writeMask = WGPUColorWriteMask_All;

        // fragment state
        WGPUFragmentState fragmentState;
        fragmentState.nextInChain = nullptr;
        fragmentState.module = shaderModule;
        fragmentState.entryPoint = fragmentEntryPoint.c_str();
        fragmentState.targetCount = 1;
        fragmentState.targets = &colorTargetState;
        fragmentState.constantCount = 0;

        // MULTISAMPLE STATE
        WGPUMultisampleState multisampleState;
        multisampleState.nextInChain = nullptr;
        multisampleState.count = 1;
        multisampleState.mask = 0xFFFFFFFF;
        multisampleState.alphaToCoverageEnabled = false;

        // PIPELINE
        WGPURenderPipelineDescriptor renderPipelineDescriptor;
        renderPipelineDescriptor.nextInChain = nullptr;
        renderPipelineDescriptor.label = label.c_str();
        renderPipelineDescriptor.layout = pipelineLayout;
        renderPipelineDescriptor.vertex = vertexState;
        renderPipelineDescriptor.fragment = &fragmentState;
        renderPipelineDescriptor.multisample = multisampleState;
        renderPipelineDescriptor.primitive.nextInChain = nullptr;
        renderPipelineDescriptor.primitive.topology = WGPUPrimitiveTopology_TriangleList;
        renderPipelineDescriptor.primitive.stripIndexFormat = WGPUIndexFormat_Undefined;
        renderPipelineDescriptor.primitive.frontFace = WGPUFrontFace_CCW;
        renderPipelineDescriptor.primitive.cullMode = WGPUCullMode_None;
        renderPipelineDescriptor.depthStencil = nullptr;

        WGPURenderPipeline renderPipeline = wgpuDeviceCreateRenderPipeline(device, &renderPipelineDescriptor);

        // release resources that are no longer needed
        for(size_t i = 0; i < vertexBufferLayoutCount; i++)
        {
            delete[] vertexBufferLayouts[i].attributes;
        }
        delete[] vertexBufferLayouts;

        if(renderPipeline == nullptr)
        {
            std::string msg = "WebGPURenderPipelineUtil::Create: Failed to create render pipeline.";
            LOG(msg);
            BREAKPOINT();
            throw std::runtime_error(msg);
        }

        return renderPipeline;
    }

    void WebGPURenderPipelineUtil::Dispose(WGPURenderPipeline renderPipeline)
    {
        wgpuRenderPipelineRelease(renderPipeline);
    }
}

#endif