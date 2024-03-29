#if USE_WEBGPU

#include "material/test/wgpu/WebGPUNoMeshTestMaterial.hpp"
#include "util/WebGPUShaderModuleUtil.hpp"

#include "bns_framework.hpp"

namespace bns
{
    WebGPUNoMeshTestMaterial::WebGPUNoMeshTestMaterial(Renderer *renderer, FileLoader *fileLoader)
        : m_renderer(static_cast<WebGPURenderer *>(renderer)), m_fileLoader(fileLoader)
    {
    }

    WebGPUNoMeshTestMaterial::~WebGPUNoMeshTestMaterial()
    {
    }

    void WebGPUNoMeshTestMaterial::Initialize()
    {
        std::string shaderSource = m_fileLoader->LoadFile("shaders/webgpu/no_mesh_test_shader.wgsl");
        WGPUShaderModule shaderModule = WebGPUShaderModuleUtil::Create(m_renderer->GetDevice(), shaderSource);

        WGPURenderPipelineDescriptor descriptor = {};

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

        descriptor.vertex.module = shaderModule;
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

        m_pipeline = wgpuDeviceCreateRenderPipeline(m_renderer->GetDevice(), &descriptor);
    }

    /**
     * @brief Render the passed in mesh.
     * @param camera The camera to render the mesh with.
     * @param mesh The mesh to render.
     * @return void
     */
    void WebGPUNoMeshTestMaterial::Draw(const Camera &camera, Mesh *mesh)
    {
        WGPURenderPassEncoder passEncoder = m_renderer->GetCurrentRenderPassEncoder();
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
    void WebGPUNoMeshTestMaterial::Draw(const Camera &camera, const Mesh &mesh, std::vector<Mat4x4f> transforms)
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
    void WebGPUNoMeshTestMaterial::DrawInstancedPrefilled(const Camera &camera, const Mesh &mesh, f32 *flatTransformsArray, i32 nOfInstances)
    {
        WGPURenderPassEncoder passEncoder = m_renderer->GetCurrentRenderPassEncoder();
        wgpuRenderPassEncoderSetPipeline(passEncoder, m_pipeline);
        wgpuRenderPassEncoderDraw(passEncoder, 3, 1, 0, 0);
    }

    /**
     * @brief Create a new copy of material
     */
    Material *WebGPUNoMeshTestMaterial::Copy() { return new WebGPUNoMeshTestMaterial(m_renderer, m_fileLoader); }

}

#endif 