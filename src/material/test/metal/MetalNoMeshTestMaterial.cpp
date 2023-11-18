#if USE_METAL

#include "material/test/metal/MetalNoMeshTestMaterial.hpp"
#include "Framework.hpp"
#include "MetalUtil.hpp"

namespace bns
{
    MetalNoMeshTestMaterial::MetalNoMeshTestMaterial(Renderer &renderer, FileLoader &fileLoader)
        : m_renderer(static_cast<MetalRenderer &>(renderer)), m_fileLoader(fileLoader)
    {
    }

    MetalNoMeshTestMaterial::~MetalNoMeshTestMaterial()
    {
    }

    void MetalNoMeshTestMaterial::Initialize()
    {
        std::string shaderSource = m_fileLoader.LoadFile("shaders/metal/no_mesh_test_shader.metal");

        MTL::Device *device = m_renderer.GetDevice();

        NS::Error *pError = nullptr;
        MTL::Library *pLibrary = device->newLibrary(NS::String::string(shaderSource.c_str(), NS::StringEncoding::UTF8StringEncoding), nullptr, &pError);
        if (!pLibrary)
        {
            printf("%s", pError->localizedDescription()->utf8String());
            assert(false);
        }

        MTL::Function *pVertexFn = pLibrary->newFunction(NS::String::string("vs_main", NS::StringEncoding::UTF8StringEncoding));
        MTL::Function *pFragFn = pLibrary->newFunction(NS::String::string("fs_main", NS::StringEncoding::UTF8StringEncoding));

        MTL::RenderPipelineDescriptor *pDesc = MetalUtil::RenderPipelineDescriptor.Create(pVertexFn, pFragFn);

        m_pipeline = device->newRenderPipelineState(pDesc, &pError);
        if (!m_pipeline)
        {
            printf("%s", pError->localizedDescription()->utf8String());
            assert(false);
        }

        pVertexFn->release();
        pFragFn->release();
        pDesc->release();
        pLibrary->release();
    }

    /**
     * @brief Render the passed in mesh.
     * @param camera The camera to render the mesh with.
     * @param mesh The mesh to render.
     * @return void
     */
    void MetalNoMeshTestMaterial::Draw(const Camera &camera, Mesh *mesh)
    {
        MTL::RenderCommandEncoder *renderCommandEncoder = m_renderer.GetRenderCommandEncoder();
        renderCommandEncoder->setRenderPipelineState(m_pipeline);
        renderCommandEncoder->drawPrimitives(MTL::PrimitiveType::PrimitiveTypeTriangle, NS::UInteger(0), NS::UInteger(3));
    }

    /**
     * @brief Render the passed in mesh multiple times.
     * If transform is empty, then the mesh will be ignored.
     * @param camera The camera to render the mesh with.
     * @param mesh The mesh to render.
     * @param transforms The transforms to render the mesh with.
     * @return void
     */
    void MetalNoMeshTestMaterial::Draw(const Camera &camera, const Mesh &mesh, std::vector<Mat4x4f> transforms)
    {
        MTL::RenderCommandEncoder *renderCommandEncoder = m_renderer.GetRenderCommandEncoder();
        renderCommandEncoder->setRenderPipelineState(m_pipeline);
        renderCommandEncoder->drawPrimitives(MTL::PrimitiveType::PrimitiveTypeTriangle, NS::UInteger(0), NS::UInteger(3));
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
    void MetalNoMeshTestMaterial::DrawInstancedPrefilled(const Camera &camera, const Mesh &mesh, f32 *flatTransformsArray, i32 nOfInstances)
    {
        MTL::RenderCommandEncoder *renderCommandEncoder = m_renderer.GetRenderCommandEncoder();
        renderCommandEncoder->setRenderPipelineState(m_pipeline);
        renderCommandEncoder->drawPrimitives(MTL::PrimitiveType::PrimitiveTypeTriangle, NS::UInteger(0), NS::UInteger(3));
    }

    /**
     * @brief Create a new copy of material
     */
    Material *MetalNoMeshTestMaterial::Copy() { return new MetalNoMeshTestMaterial(m_renderer, m_fileLoader); }
}

#endif // __APPLE__