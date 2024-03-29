#if USE_WEBGPU

#include "material/test/wgpu/WebGPUBasicMeshTexturedTestMaterial.hpp"
#include "mesh/wgpu/WebGPUMesh.hpp"
#include "bns_framework.hpp"
#include "texture/bns_webgpu_texture2d.hpp"
#include "util/WebGPUShaderModuleUtil.hpp"

#include "util/WebGPUVertexBufferLayoutUtil.hpp"
#include "bns_webgpu_util.hpp"

namespace bns
{
    WebGPUBasicMeshTexturedTestMaterial::WebGPUBasicMeshTexturedTestMaterial(Renderer *renderer, FileLoader *fileLoader, Texture2D *texture)
        : m_renderer(static_cast<WebGPURenderer *>(renderer)), m_fileLoader(fileLoader), m_texture(texture)
    {
    }

    WebGPUBasicMeshTexturedTestMaterial::~WebGPUBasicMeshTexturedTestMaterial()
    {
    }

    void WebGPUBasicMeshTexturedTestMaterial::Initialize()
    {
        std::string shaderSource = m_fileLoader->LoadFile("shaders/webgpu/basic_mesh_textured_test_shader.wgsl");
        WGPUShaderModule shaderModule = WebGPUShaderModuleUtil::Create(m_renderer->GetDevice(), shaderSource);

        WGPURenderPipelineDescriptor descriptor = {};

        // Create vertex layouts description
        std::vector<BufferLayoutDescriptor> vertexLayoutDescriptors;
        BufferLayoutDescriptor bufferLayoutDesc;
        bufferLayoutDesc.Stride = 9 * sizeof(float);
        bufferLayoutDesc.Attributes.push_back({VertexFormat::Float32x3, 0, 0}); // format, shader location, offset
        bufferLayoutDesc.Attributes.push_back({VertexFormat::Float32x2, 1, 3 * sizeof(float)});
        bufferLayoutDesc.Attributes.push_back({VertexFormat::Float32x4, 2, 5 * sizeof(float)});
        vertexLayoutDescriptors.push_back(bufferLayoutDesc);

        // Create vertex buffer layout
        size_t vertexBuffersLayoutCount;
        WGPUVertexBufferLayout *wgpuVertexBufferLayouts = WebGPUVertexBufferLayoutUtil::Create(vertexLayoutDescriptors, &vertexBuffersLayoutCount);

        descriptor.vertex.module = shaderModule;
        descriptor.vertex.entryPoint = "vs_main";
        descriptor.vertex.bufferCount = vertexBuffersLayoutCount;
        descriptor.vertex.buffers = &wgpuVertexBufferLayouts[0];

        // Fragment state
        // Fragment state
        WGPUBlendState blend = {};
        blend.color.operation = WGPUBlendOperation_Add;
        blend.color.srcFactor = WGPUBlendFactor_One;
        blend.color.dstFactor = WGPUBlendFactor_OneMinusSrcAlpha;
        blend.alpha.operation = WGPUBlendOperation_Add;
        blend.alpha.srcFactor = WGPUBlendFactor_One;
        blend.alpha.dstFactor = WGPUBlendFactor_OneMinusSrcAlpha;

        // default color target state
        WGPUColorTargetState colorTarget = {};
        colorTarget.nextInChain = nullptr;
        colorTarget.format = WGPUTextureFormat_BGRA8Unorm;
        colorTarget.blend = &blend;
        colorTarget.writeMask = WGPUColorWriteMask_All;
        std::string fragFn = "fs_main";
        WGPUFragmentState fragment = WebGPUUtil::FragmentState.Create(shaderModule, colorTarget, fragFn);
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

        m_sourceTextureBindGroupLayout =
            wgpuDeviceCreateBindGroupLayout(m_renderer->GetDevice(), &bindGroupLayoutDescriptor);

        WGPUPipelineLayoutDescriptor pipelineLayoutDescriptor = {};
        pipelineLayoutDescriptor.nextInChain = nullptr;
        pipelineLayoutDescriptor.bindGroupLayoutCount = 1;
        pipelineLayoutDescriptor.bindGroupLayouts = &m_sourceTextureBindGroupLayout;
        descriptor.layout = wgpuDeviceCreatePipelineLayout(m_renderer->GetDevice(), &pipelineLayoutDescriptor);

        descriptor.depthStencil = nullptr;

        descriptor.multisample.count = 1;
        descriptor.multisample.mask = 0xFFFFFFFF;
        descriptor.multisample.alphaToCoverageEnabled = false;

        descriptor.primitive.frontFace = WGPUFrontFace_CCW;
        descriptor.primitive.cullMode = WGPUCullMode_None;
        descriptor.primitive.topology = WGPUPrimitiveTopology_TriangleList;
        descriptor.primitive.stripIndexFormat = WGPUIndexFormat_Undefined;

        m_pipeline = wgpuDeviceCreateRenderPipeline(m_renderer->GetDevice(), &descriptor);

        WebGPUTexture2D *texture = static_cast<WebGPUTexture2D *>(m_texture);

        WGPUBindGroupDescriptor bindGroupDescriptor = {};
        bindGroupDescriptor.nextInChain = nullptr;
        bindGroupDescriptor.layout = m_sourceTextureBindGroupLayout;
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
        textureViewDesc.label = "texture_view";
        textureViewDesc.aspect = WGPUTextureAspect_All;
        textureViewDesc.baseArrayLayer = 0;
        textureViewDesc.arrayLayerCount = 1;
        textureViewDesc.baseMipLevel = 0;
        textureViewDesc.mipLevelCount = 1;
        textureViewDesc.dimension = WGPUTextureViewDimension_2D;
        textureViewDesc.format = WGPUTextureFormat_RGBA8Unorm;
        WGPUTextureView textureView = wgpuTextureCreateView(texture->Texture, &textureViewDesc);
        bindGroupEntries[1].textureView = textureView;
        bindGroupDescriptor.entries = &bindGroupEntries[0];

        m_sourceTextureBindGroup = wgpuDeviceCreateBindGroup(m_renderer->GetDevice(), &bindGroupDescriptor);

        WebGPUVertexBufferLayoutUtil::Delete(wgpuVertexBufferLayouts, 1);
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
        WGPURenderPassEncoder passEncoder = m_renderer->GetCurrentRenderPassEncoder();

        wgpuRenderPassEncoderSetPipeline(passEncoder, m_pipeline);
        wgpuRenderPassEncoderSetIndexBuffer(passEncoder, webGPUMesh.IndexBuffer, webGPUMesh.IndexFormat, 0, 6 * sizeof(u32));
        wgpuRenderPassEncoderSetVertexBuffer(passEncoder, 0, webGPUMesh.VertexBuffer, 0, webGPUMesh.VertexBufferSize);
        wgpuRenderPassEncoderSetBindGroup(passEncoder, 0, m_sourceTextureBindGroup, 0, 0);
        wgpuRenderPassEncoderDrawIndexed(passEncoder, 6, 1, 0, 0, 0);
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
        WGPURenderPassEncoder passEncoder = m_renderer->GetCurrentRenderPassEncoder();
        wgpuRenderPassEncoderSetPipeline(passEncoder, m_pipeline);
        wgpuRenderPassEncoderDraw(passEncoder, 3, 1, 0, 0);
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
        WGPURenderPassEncoder passEncoder = m_renderer->GetCurrentRenderPassEncoder();
        wgpuRenderPassEncoderSetPipeline(passEncoder, m_pipeline);
        wgpuRenderPassEncoderDraw(passEncoder, 3, 1, 0, 0);
    }

    /**
     * @brief Create a new copy of material
     */
    Material *WebGPUBasicMeshTexturedTestMaterial::Copy() { return new WebGPUBasicMeshTexturedTestMaterial(m_renderer, m_fileLoader, m_texture); }

}

#endif 