#if USE_WEBGPU

#include "material/test/wgpu/WebGPUBasicMeshTestMaterial.hpp"
#include "util/WebGPUShaderModuleUtil.hpp"
#include "mesh/wgpu/WebGPUMesh.hpp"
#include "Framework.hpp"

namespace bns
{
    WebGPUBasicMeshTestMaterial::WebGPUBasicMeshTestMaterial(Renderer *renderer, FileLoader *fileLoader)
        : m_renderer(static_cast<WebGPURenderer *>(renderer)), m_fileLoader(fileLoader)
    {
    }

    WebGPUBasicMeshTestMaterial::~WebGPUBasicMeshTestMaterial()
    {
    }

    void WebGPUBasicMeshTestMaterial::Initialize()
    {
        std::string shaderSource = m_fileLoader->LoadFile("shaders/webgpu/basic_mesh_test_shader.wgsl");
        WGPUShaderModule shaderModule = WebGPUShaderModuleUtil::Create(m_renderer->GetDevice(), shaderSource);

        WGPURenderPipelineDescriptor descriptor = {};

        // Vertex state
        WGPUVertexBufferLayout buffersLayout[2];
        buffersLayout[0].arrayStride = 3 * sizeof(float);
        buffersLayout[0].stepMode = WGPUVertexStepMode::WGPUVertexStepMode_Vertex;
        buffersLayout[0].attributeCount = 1;
        WGPUVertexAttribute positionAttribute;
        positionAttribute.format = WGPUVertexFormat_Float32x3;
        positionAttribute.offset = 0;
        positionAttribute.shaderLocation = 0;
        buffersLayout[0].attributes = &positionAttribute;

        buffersLayout[1].arrayStride = 4 * sizeof(float);
        buffersLayout[1].stepMode = WGPUVertexStepMode::WGPUVertexStepMode_Vertex;
        buffersLayout[1].attributeCount = 1;
        WGPUVertexAttribute colorAttribute;
        colorAttribute.format = WGPUVertexFormat_Float32x4;
        colorAttribute.offset = 0;
        colorAttribute.shaderLocation = 1;
        buffersLayout[1].attributes = &colorAttribute;
        descriptor.vertex.module = shaderModule;
        descriptor.vertex.entryPoint = "vs_main";
        descriptor.vertex.bufferCount = 2;
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
        descriptor.layout = nullptr;
        descriptor.depthStencil = nullptr;

        descriptor.multisample.count = 1;
        descriptor.multisample.mask = 0xFFFFFFFF;
        descriptor.multisample.alphaToCoverageEnabled = false;

        descriptor.primitive.frontFace = WGPUFrontFace_CCW;
        descriptor.primitive.cullMode = WGPUCullMode_None;
        descriptor.primitive.topology = WGPUPrimitiveTopology_TriangleList;
        descriptor.primitive.stripIndexFormat = WGPUIndexFormat_Undefined;

        m_pipeline = wgpuDeviceCreateRenderPipeline(m_renderer->GetDevice(), &descriptor);
    }

    /**
     * @brief Render the passed in mesh.
     * @param camera The camera to render the mesh with.
     * @param mesh The mesh to render.
     * @return void
     */
    void WebGPUBasicMeshTestMaterial::Draw(const Camera &camera, Mesh *mesh)
    {
        WebGPUMesh webGPUMesh = *static_cast<WebGPUMesh *>(mesh);
        WGPURenderPassEncoder passEncoder = m_renderer->GetCurrentPassEncoder();

        wgpuRenderPassEncoderSetVertexBuffer(passEncoder, 0, webGPUMesh.VertexPositionsBuffer, 0, webGPUMesh.VertexPositionsBufferSize);
        wgpuRenderPassEncoderSetVertexBuffer(passEncoder, 1, webGPUMesh.VertexColorsBuffer, 0, webGPUMesh.VertexColorsBufferSize);
        wgpuRenderPassEncoderSetPipeline(passEncoder, m_pipeline);
        wgpuRenderPassEncoderDraw(passEncoder, 3, 1, 0, 0);
    }

    /**
     * @brief Render the passed in mesh multiple times.
     * If transform is empty, then the mesh will be ignored.
     * @param camera The camera to render the mesh with.
     * @param mesh The mesh to render.
     * @param transforms The transforms to render the mesh with.
     * @return void
     */
    void WebGPUBasicMeshTestMaterial::Draw(const Camera &camera, const Mesh &mesh, std::vector<Mat4x4f> transforms)
    {
        WGPURenderPassEncoder passEncoder = m_renderer->GetCurrentPassEncoder();

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
    void WebGPUBasicMeshTestMaterial::DrawInstancedPrefilled(const Camera &camera, const Mesh &mesh, f32 *flatTransformsArray, i32 nOfInstances)
    {
        WGPURenderPassEncoder passEncoder = m_renderer->GetCurrentPassEncoder();

        wgpuRenderPassEncoderSetPipeline(passEncoder, m_pipeline);
        wgpuRenderPassEncoderDraw(passEncoder, 3, 1, 0, 0);
    }

    /**
     * @brief Create a new copy of material
     */
    Material *WebGPUBasicMeshTestMaterial::Copy() { return new WebGPUBasicMeshTestMaterial(m_renderer, m_fileLoader); }

}

#endif 