#include "material/test/wgpu/WebGPUBasicMeshTexturedTestMaterial.hpp"
#include "renderer/common/WebGPURenderPipelineUtil.hpp"
#include "mesh/wgpu/WebGPUMesh.hpp"
#include "Framework.hpp"
#include "textures/wgpu/WebGPUTexture2D.hpp"

namespace bns
{
    WebGPUBasicMeshTexturedTestMaterial::WebGPUBasicMeshTexturedTestMaterial(Framework &framework, Texture2D *texture)
        : m_framework(framework), m_texture(texture)
    {
    }

    WebGPUBasicMeshTexturedTestMaterial::~WebGPUBasicMeshTexturedTestMaterial()
    {
    }

    void WebGPUBasicMeshTexturedTestMaterial::Initialize()
    {
        std::string shaderSource = m_framework.FileLoader.OpenFile("shaders/webgpu/basic_mesh_textured_test_shader.wgsl");
        WGPUShaderModule shaderModule = WebGPURenderPipelineUtil::CreateShaderModule(m_framework.Context.WebGPUDevice, shaderSource);

        WGPURenderPipelineDescriptor descriptor = {};

        // Vertex state
        WGPUVertexBufferLayout buffersLayout[3];

        // Position
        buffersLayout[0].arrayStride = 3 * sizeof(float);
        buffersLayout[0].stepMode = WGPUVertexStepMode::WGPUVertexStepMode_Vertex;
        buffersLayout[0].attributeCount = 1;
        WGPUVertexAttribute positionAttribute;
        positionAttribute.format = WGPUVertexFormat_Float32x3;
        positionAttribute.offset = 0;
        positionAttribute.shaderLocation = 0;
        buffersLayout[0].attributes = &positionAttribute;

        // Color
        buffersLayout[1].arrayStride = 4 * sizeof(float);
        buffersLayout[1].stepMode = WGPUVertexStepMode::WGPUVertexStepMode_Vertex;
        buffersLayout[1].attributeCount = 1;
        WGPUVertexAttribute colorAttribute;
        colorAttribute.format = WGPUVertexFormat_Float32x4;
        colorAttribute.offset = 0;
        colorAttribute.shaderLocation = 1;
        buffersLayout[1].attributes = &colorAttribute;

        // tex coords
        buffersLayout[2].arrayStride = 2 * sizeof(float);
        buffersLayout[2].stepMode = WGPUVertexStepMode::WGPUVertexStepMode_Vertex;
        buffersLayout[2].attributeCount = 1;
        WGPUVertexAttribute texCoordsAttribute;
        texCoordsAttribute.format = WGPUVertexFormat_Float32x2;
        texCoordsAttribute.offset = 0;
        texCoordsAttribute.shaderLocation = 2;
        buffersLayout[2].attributes = &texCoordsAttribute;

        descriptor.vertex.module = shaderModule;
        descriptor.vertex.entryPoint = "vs_main";
        descriptor.vertex.bufferCount = 3;
        descriptor.vertex.buffers = &buffersLayout[0];

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

        WGPUFragmentState fragment = {};
        fragment.nextInChain = nullptr;
        fragment.module = shaderModule;
        fragment.entryPoint = "fs_main";
        fragment.targetCount = 1;
        fragment.targets = &colorTarget;
        descriptor.fragment = &fragment;

        // Other state
        WGPUBindGroupLayoutDescriptor bindGroupLayoutDescriptor = {};
        bindGroupLayoutDescriptor.nextInChain = nullptr;
        bindGroupLayoutDescriptor.entryCount = 2;
        WGPUBindGroupLayoutEntry bindGroupLayoutEntry[2];

        // Uniform buffer group 0 binding 0
        bindGroupLayoutEntry[0].nextInChain = nullptr;
        bindGroupLayoutEntry[0].binding = 0;
        bindGroupLayoutEntry[0].visibility = WGPUShaderStage_Fragment;
        bindGroupLayoutEntry[0].sampler.type = WGPUSamplerBindingType_Filtering;            // setup sampler
        bindGroupLayoutEntry[0].buffer.type = WGPUBufferBindingType_Undefined;              // buffer is not used
        bindGroupLayoutEntry[0].texture.sampleType = WGPUTextureSampleType_Undefined;       // texture is not used
        bindGroupLayoutEntry[0].storageTexture.access = WGPUStorageTextureAccess_Undefined; // storage texture is not used

        // Uniform buffer group 0 binding 1
        bindGroupLayoutEntry[1].nextInChain = nullptr;
        bindGroupLayoutEntry[1].binding = 1;
        bindGroupLayoutEntry[1].visibility = WGPUShaderStage_Fragment;
        WGPUTextureBindingLayout textureBindingLayout = {};
        textureBindingLayout.sampleType = WGPUTextureSampleType_Float;
        textureBindingLayout.viewDimension = WGPUTextureViewDimension_2D;
        bindGroupLayoutEntry[1].texture = textureBindingLayout;
        bindGroupLayoutEntry[1].buffer.type = WGPUBufferBindingType_Undefined;              // buffer is not used
        bindGroupLayoutEntry[1].storageTexture.access = WGPUStorageTextureAccess_Undefined; // storage texture is not used
        bindGroupLayoutEntry[1].sampler.type = WGPUSamplerBindingType_Undefined;            // sampler is not used

        bindGroupLayoutDescriptor.entries = &bindGroupLayoutEntry[0];

        m_textureBindGroupLayout =
            wgpuDeviceCreateBindGroupLayout(m_framework.Context.WebGPUDevice, &bindGroupLayoutDescriptor);

        WGPUPipelineLayoutDescriptor pipelineLayoutDescriptor = {};
        pipelineLayoutDescriptor.nextInChain = nullptr;
        pipelineLayoutDescriptor.bindGroupLayoutCount = 1;
        pipelineLayoutDescriptor.bindGroupLayouts = &m_textureBindGroupLayout;
        descriptor.layout = wgpuDeviceCreatePipelineLayout(m_framework.Context.WebGPUDevice, &pipelineLayoutDescriptor);

        descriptor.depthStencil = nullptr;

        descriptor.multisample.count = 1;
        descriptor.multisample.mask = 0xFFFFFFFF;
        descriptor.multisample.alphaToCoverageEnabled = false;

        descriptor.primitive.frontFace = WGPUFrontFace_CCW;
        descriptor.primitive.cullMode = WGPUCullMode_None;
        descriptor.primitive.topology = WGPUPrimitiveTopology_TriangleList;
        descriptor.primitive.stripIndexFormat = WGPUIndexFormat_Undefined;

        m_pipeline = wgpuDeviceCreateRenderPipeline(m_framework.Context.WebGPUDevice, &descriptor);

        WebGPUTexture2D *texture = static_cast<WebGPUTexture2D *>(m_texture);

        WGPUBindGroupDescriptor bindGroupDescriptor = {};
        bindGroupDescriptor.nextInChain = nullptr;
        bindGroupDescriptor.layout = m_textureBindGroupLayout;
        bindGroupDescriptor.entryCount = 2;
        WGPUBindGroupEntry bindGroupEntries[2];
        bindGroupEntries[0].nextInChain = nullptr;
        bindGroupEntries[0].binding = 0;
        bindGroupEntries[0].buffer = nullptr;
        bindGroupEntries[0].textureView = nullptr;
        bindGroupEntries[0].sampler = texture->Sampler;
        bindGroupEntries[1].nextInChain = nullptr;
        bindGroupEntries[1].binding = 1;
        bindGroupEntries[1].buffer = nullptr;
        bindGroupEntries[1].sampler = nullptr;
        WGPUTextureViewDescriptor textureViewDesc;
        textureViewDesc.nextInChain = nullptr;
        textureViewDesc.aspect = WGPUTextureAspect_All;
        textureViewDesc.baseArrayLayer = 0;
        textureViewDesc.arrayLayerCount = 1;
        textureViewDesc.baseMipLevel = 0;
        textureViewDesc.mipLevelCount = 1;
        textureViewDesc.dimension = WGPUTextureViewDimension_2D;
        textureViewDesc.format  = WGPUTextureFormat_RGBA8Unorm;
        WGPUTextureView textureView = wgpuTextureCreateView(texture->Texture, &textureViewDesc);
        bindGroupEntries[1].textureView = textureView;
        bindGroupDescriptor.entries = &bindGroupEntries[0];

        m_textureBindGroup = wgpuDeviceCreateBindGroup(
            m_framework.Context.WebGPUDevice, &bindGroupDescriptor);
    }

    /**
     * @brief Render the passed in mesh.
     * @param camera The camera to render the mesh with.
     * @param mesh The mesh to render.
     * @return void
     */
    void WebGPUBasicMeshTexturedTestMaterial::Draw(const Camera &camera, Mesh *mesh)
    {
        WebGPUMesh webGPUMesh = *static_cast<WebGPUMesh *>(mesh);
        WGPURenderPassEncoder passEncoder = m_framework.Context.CurrentWebGPURenderPassEncoder;

        wgpuRenderPassEncoderSetPipeline(passEncoder, m_pipeline);
        wgpuRenderPassEncoderSetVertexBuffer(passEncoder, 0, webGPUMesh.VertexPositionsBuffer, 0, webGPUMesh.VertexPositionsBufferSize);
        wgpuRenderPassEncoderSetVertexBuffer(passEncoder, 1, webGPUMesh.VertexColorsBuffer, 0, webGPUMesh.VertexColorsBufferSize);
        wgpuRenderPassEncoderSetVertexBuffer(passEncoder, 2, webGPUMesh.TextureCoordinatesBuffer, 0, webGPUMesh.TextureCoordinatesBufferSize);
        wgpuRenderPassEncoderSetBindGroup(passEncoder, 0, m_textureBindGroup, 0, 0);
        wgpuRenderPassEncoderDraw(m_framework.Context.CurrentWebGPURenderPassEncoder, 6, 1, 0, 0);
    }

    /**
     * @brief Render the passed in mesh multiple times.
     * If transform is empty, then the mesh will be ignored.
     * @param camera The camera to render the mesh with.
     * @param mesh The mesh to render.
     * @param transforms The transforms to render the mesh with.
     * @return void
     */
    void WebGPUBasicMeshTexturedTestMaterial::Draw(const Camera &camera, const Mesh &mesh, std::vector<Mat4x4f> transforms)
    {
        wgpuRenderPassEncoderSetPipeline(m_framework.Context.CurrentWebGPURenderPassEncoder, m_pipeline);
        wgpuRenderPassEncoderDraw(m_framework.Context.CurrentWebGPURenderPassEncoder, 3, 1, 0, 0);
    }

    /**
     * @brief Render the passed in mesh multiple times.
     * Use flat transforms array where array is already prefilled with transforms matrices. Avoids copying of transforms to buffer.
     * @param camera The camera to render the mesh with.
     * @param mesh The mesh to render.
     * @param flatTransformsArray The flat array of transforms to render the mesh with. Array must be of length 16 * nOfInstances.
     * @param nOfInstances The number of instances to render.
     * @return void
     */
    void WebGPUBasicMeshTexturedTestMaterial::DrawInstancedPrefilled(const Camera &camera, const Mesh &mesh, f32 *flatTransformsArray, i32 nOfInstances)
    {
        wgpuRenderPassEncoderSetPipeline(m_framework.Context.CurrentWebGPURenderPassEncoder, m_pipeline);
        wgpuRenderPassEncoderDraw(m_framework.Context.CurrentWebGPURenderPassEncoder, 3, 1, 0, 0);
    }

    /**
     * @brief Create a new copy of material
     */
    Material *WebGPUBasicMeshTexturedTestMaterial::Copy() { return new WebGPUBasicMeshTexturedTestMaterial(m_framework, m_texture); }

}
