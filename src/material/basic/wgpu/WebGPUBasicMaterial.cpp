
#include "Framework.hpp"
#include "material/basic/wgpu/WebGPUBasicMaterial.hpp"
#include "util/wgpu/WebGPUShaderModuleUtil.hpp"
#include "renderer/common/WebGPURenderPipelineUtil.hpp"
#include "mesh/wgpu/WebGPUMesh.hpp"
#include <iostream>

namespace bns
{
    WebGPUBasicMaterial::WebGPUBasicMaterial(Framework &framework)
        : BasicMaterial()
    {
        m_framework = &framework;
        m_maxInstances = 1;
        DiffuseColor = Color::LightGray();
    }

    WebGPUBasicMaterial::WebGPUBasicMaterial(Framework &framework, i32 maxInstances)
        : BasicMaterial(), m_maxInstances(maxInstances)
    {
        m_framework = &framework;
        DiffuseColor = Color::LightGray();
    }

    void WebGPUBasicMaterial::Initialize()
    {
        auto states = InitializeStates();
        InitializeBuffersResult buffers = InitializeBuffers();

        WGPUDevice device = m_framework->Context.WebGPUDevice;

        WGPUPipelineLayoutDescriptor pipelineLayoutDesc;
        pipelineLayoutDesc.label = "Basic Material Pipeline Layout";
        pipelineLayoutDesc.nextInChain = nullptr;
        pipelineLayoutDesc.bindGroupLayoutCount = 1;
        pipelineLayoutDesc.bindGroupLayouts = &buffers.UniformsBindGroupLayout;

        WGPUPipelineLayout pipelineLayout = wgpuDeviceCreatePipelineLayout(device, &pipelineLayoutDesc);

        WGPURenderPipelineDescriptor pipelineDesc = WebGPURenderPipelineUtil::Create(
            pipelineLayout,
            states.VertexState,
            states.FragmentState);

        // release shader modules
      //   wgpuShaderModuleRelease(states.VertexState.module);
     //   wgpuShaderModuleRelease(states.FragmentState.module);

        WGPURenderPipeline pipeline = wgpuDeviceCreateRenderPipeline(device, &pipelineDesc);
        m_pipeline = pipeline;
    }

    WebGPUBasicMaterial::InitializeStatesResult WebGPUBasicMaterial::InitializeStates()
    {
        WGPUDevice device = static_cast<WGPUDevice>(m_framework->Context.WebGPUDevice);

        std::string shaderSource = m_framework->FileLoader.OpenFile("shaders/webgpu/basic_material_shader.wgsl");

        std::cout << shaderSource << std::endl;

        WGPUShaderModule shaderModule = WebGPUShaderModuleUtil::Create(device, shaderSource);

        // 2 buffers
        WGPUVertexBufferLayout vertexBufferLayout[2];

        // attribute of first buffer
        WGPUVertexAttribute positionAttribute;
        positionAttribute.shaderLocation = 0;
        positionAttribute.offset = 0;
        positionAttribute.format = WGPUVertexFormat::WGPUVertexFormat_Float32x3;

        // layout of first buffer
        vertexBufferLayout[0].arrayStride = sizeof(f32) * 3;
        vertexBufferLayout[0].stepMode = WGPUVertexStepMode::WGPUVertexStepMode_Vertex;
        vertexBufferLayout[0].attributeCount = 1;
        vertexBufferLayout[0].attributes = &positionAttribute;

        // attribute of second buffer
        WGPUVertexAttribute colorAttribute;
        colorAttribute.shaderLocation = 1;
        colorAttribute.offset = 0;
        colorAttribute.format = WGPUVertexFormat::WGPUVertexFormat_Float32x4;

        // layout of second buffer
        vertexBufferLayout[1].arrayStride = sizeof(f32) * 4;
        vertexBufferLayout[1].stepMode = WGPUVertexStepMode::WGPUVertexStepMode_Vertex;
        vertexBufferLayout[1].attributeCount = 1;
        vertexBufferLayout[1].attributes = &colorAttribute;

        WGPUVertexState vertexState;
        vertexState.module = shaderModule;
        vertexState.entryPoint = "vs_main";
        vertexState.bufferCount = 2;
        vertexState.buffers = vertexBufferLayout;

        // Fragment state
        WGPUBlendState blend = {};
        blend.color.operation = WGPUBlendOperation_Add;
        blend.color.srcFactor = WGPUBlendFactor_One;
        blend.color.dstFactor = WGPUBlendFactor_OneMinusSrcAlpha;
        blend.alpha.operation = WGPUBlendOperation_Add;
        blend.alpha.srcFactor = WGPUBlendFactor_One;
        blend.alpha.dstFactor = WGPUBlendFactor_OneMinusSrcAlpha;

        WGPUColorTargetState colorTarget = {};
        colorTarget.nextInChain = nullptr;
        colorTarget.format = WGPUTextureFormat_BGRA8Unorm;
        colorTarget.blend = &blend;
        colorTarget.writeMask = WGPUColorWriteMask_All;

        WGPUFragmentState fragmentState = {};
        fragmentState.nextInChain = nullptr;
        fragmentState.module = shaderModule;
        fragmentState.entryPoint = "fs_main";
        fragmentState.targetCount = 1;
        fragmentState.targets = &colorTarget;

        return {vertexState, fragmentState};
    }

    WebGPUBasicMaterial::InitializeBuffersResult WebGPUBasicMaterial::InitializeBuffers()
    {
        WGPUDevice device = static_cast<WGPUDevice>(m_framework->Context.WebGPUDevice);

        // global uniform group(0) binding(0) projectionViewMatrix, diffuseColor
        WGPUBindGroupLayoutEntry bindingLayouts[2];
        bindingLayouts[0].binding = 0;
        bindingLayouts[0].visibility = WGPUShaderStage::WGPUShaderStage_Vertex;
        bindingLayouts[0].buffer.type = WGPUBufferBindingType::WGPUBufferBindingType_Uniform;
        bindingLayouts[0].buffer.minBindingSize = sizeof(Mat4x4f) + sizeof(Color);

        // instance uniform group(0) binding(1)
        bindingLayouts[1].binding = 1;
        bindingLayouts[1].visibility = WGPUShaderStage::WGPUShaderStage_Vertex;
        bindingLayouts[1].buffer.type = WGPUBufferBindingType::WGPUBufferBindingType_ReadOnlyStorage;
        bindingLayouts[1].buffer.hasDynamicOffset = false;
        bindingLayouts[1].buffer.minBindingSize = sizeof(Mat4x4f) * m_maxInstances;

        WGPUBindGroupLayoutDescriptor bindGroupLayoutDesc;
        bindGroupLayoutDesc.entryCount = 2;
        bindGroupLayoutDesc.nextInChain = nullptr;
        bindGroupLayoutDesc.entries = &bindingLayouts[0];
        bindGroupLayoutDesc.label = "basic_material_layout";

        WGPUBindGroupLayout uniformBindGroupLayout = wgpuDeviceCreateBindGroupLayout(device, &bindGroupLayoutDesc);

        // global uniform buffer
        WGPUBufferDescriptor uniformGlobalBufferDesc;
        uniformGlobalBufferDesc.nextInChain = nullptr;
        uniformGlobalBufferDesc.label = "basic_material_global_uniform_buffer";
        uniformGlobalBufferDesc.size = sizeof(Mat4x4f) + sizeof(Color);
        uniformGlobalBufferDesc.usage = WGPUBufferUsage::WGPUBufferUsage_Uniform | WGPUBufferUsage::WGPUBufferUsage_CopyDst;
        uniformGlobalBufferDesc.mappedAtCreation = false;
        WGPUBuffer uniformGlobalBuffer = wgpuDeviceCreateBuffer(device, &uniformGlobalBufferDesc);
        m_uniformGlobalBuffer = uniformGlobalBuffer;

        // instance uniform buffer
        WGPUBufferDescriptor uniformInstanceBufferDesc;
        uniformInstanceBufferDesc.label = "basic_material_instance_uniform_buffer";
        uniformInstanceBufferDesc.nextInChain = nullptr;
        uniformInstanceBufferDesc.size = sizeof(Mat4x4f) * m_maxInstances;
        uniformInstanceBufferDesc.usage = WGPUBufferUsage::WGPUBufferUsage_Storage | WGPUBufferUsage::WGPUBufferUsage_CopyDst;
        uniformGlobalBufferDesc.mappedAtCreation = false;
        WGPUBuffer uniformInstancesBuffer = wgpuDeviceCreateBuffer(device, &uniformInstanceBufferDesc);
        m_uniformInstancesBuffer = uniformInstancesBuffer;

        WGPUBindGroupEntry uniformBindGroupEntries[2];
        uniformBindGroupEntries[0].binding = 0;
        uniformBindGroupEntries[0].buffer = m_uniformGlobalBuffer;
        uniformBindGroupEntries[1].binding = 1;
        uniformBindGroupEntries[1].buffer = m_uniformInstancesBuffer;

        WGPUBindGroupDescriptor uniformBindGroupDesc;
        uniformBindGroupDesc.layout = uniformBindGroupLayout;
        uniformBindGroupDesc.entryCount = 2;
        uniformBindGroupDesc.entries = &uniformBindGroupEntries[0];

        auto uniformBindGroup = wgpuDeviceCreateBindGroup(device, &uniformBindGroupDesc);
        m_uniformsBindGroup = uniformBindGroup;

        return {uniformBindGroupLayout};
    }

    /**
     * @brief Render the passed in mesh.
     * @param camera The camera to render the mesh with.
     * @param mesh The mesh to render.
     * @return void
     */
    void WebGPUBasicMaterial::Draw(const Camera &camera, Mesh *mesh)
    {
        WGPUDevice device = m_framework->Context.WebGPUDevice;
        WGPUQueue queue = wgpuDeviceGetQueue(device);
        WGPURenderPassEncoder pass = m_framework->Context.CurrentWebGPURenderPassEncoder;

        WebGPUMesh webGPUMesh = *static_cast<WebGPUMesh *>(mesh);

        wgpuRenderPassEncoderSetPipeline(pass, m_pipeline);

        // write to uniform buffer
        wgpuQueueWriteBuffer(queue, m_uniformGlobalBuffer, 0, &camera.ProjectionViewMatrix, sizeof(Mat4x4f));
        wgpuQueueWriteBuffer(queue, m_uniformGlobalBuffer, sizeof(Mat4x4f), &DiffuseColor, sizeof(Color));

        // update instance uniform buffer
        wgpuQueueWriteBuffer(queue, m_uniformInstancesBuffer, 0, &webGPUMesh.Transform, sizeof(Mat4x4f));

        wgpuRenderPassEncoderSetBindGroup(pass, 0, m_uniformsBindGroup, 0, nullptr);

        // draw
        wgpuRenderPassEncoderSetVertexBuffer(pass, 0, webGPUMesh.VertexPositionsBuffer, 0, webGPUMesh.VertexPositionsBufferSize);
        wgpuRenderPassEncoderSetVertexBuffer(pass, 1, webGPUMesh.VertexColorsBuffer, 0, webGPUMesh.VertexColorsBufferSize);
        wgpuRenderPassEncoderSetIndexBuffer(pass, webGPUMesh.IndexBuffer, webGPUMesh.IndexFormat, 0, webGPUMesh.IndicesCount * sizeof(u32));

        wgpuRenderPassEncoderDrawIndexed(pass, (uint32_t)webGPUMesh.IndicesCount, 1, 0, 0, 0);

    }

    /**
     * @brief Render the passed in mesh multiple times.
     * If transform is empty, then the mesh will be ignored.
     * @param camera The camera to render the mesh with.
     * @param mesh The mesh to render.
     * @param transforms The transforms to render the mesh with.
     * @return void
     */
    void WebGPUBasicMaterial::Draw(const Camera &camera, const Mesh &mesh, std::vector<Mat4x4f> transforms) {}

    /**
     * @brief Render the passed in mesh multiple times.
     * Use flat transforms array where array is already prefilled with transforms matrices. Avoids copying of transforms to buffer.
     * @param camera The camera to render the mesh with.
     * @param mesh The mesh to render.
     * @param flatTransformsArray The flat array of transforms to render the mesh with. Array must be of length 16 * nOfInstances.
     * @param nOfInstances The number of instances to render.
     * @return void
     */
    void WebGPUBasicMaterial::DrawInstancedPrefilled(const Camera &camera, const Mesh &mesh, f32 *flatTransformsArray, i32 nOfInstances) {}

    /**
     * @brief Create a new copy of material
     */
    Material *WebGPUBasicMaterial::Copy() { return nullptr; }
}
