#ifdef __APPLE__

#include "Framework.hpp"
#include "mesh/metal/MetalMesh.hpp"
#include "material/test/metal/MetalBasicMeshTexturedTestMaterial.hpp"
#include "MetalUtil.hpp"
#include "texture/MetalTexture2D.hpp"

namespace bns
{
    MetalBasicMeshTexturedTestMaterial::MetalBasicMeshTexturedTestMaterial(Framework &framework, Texture2D *texture)
        : m_framework(framework), m_texture(texture)
    {
        m_renderer = static_cast<MetalRenderer *>(framework.GetRenderer());
        m_pipeline = nullptr;
    }

    MetalBasicMeshTexturedTestMaterial::~MetalBasicMeshTexturedTestMaterial()
    {
    }

    void MetalBasicMeshTexturedTestMaterial::Initialize()
    {
        m_device = m_renderer->GetDevice();     
        std::string shaderSource = m_framework.FileLoader.LoadFile("shaders/metal/basic_mesh_textured_test_shader.metal");


        NS::Error *pError = nullptr;
        NS::String *pSource = NS::String::string(shaderSource.c_str(), NS::StringEncoding::UTF8StringEncoding);
        MTL::Library *pLibrary = m_device->newLibrary(pSource, nullptr, &pError);
        if (!pLibrary)
        {
            printf("%s", pError->localizedDescription()->utf8String());
            assert(false);
        }

        MTL::Function *pVertexFn = pLibrary->newFunction(NS::String::string("vs_main", NS::StringEncoding::UTF8StringEncoding));
        MTL::Function *pFragFn = pLibrary->newFunction(NS::String::string("fs_main", NS::StringEncoding::UTF8StringEncoding));

        MTL::RenderPipelineDescriptor *pDesc = MetalUtil::RenderPipelineDescriptor.Create(pVertexFn, pFragFn);

        // Setup blending

        // vertex
        MTL::VertexDescriptor *pVertexDesc = pDesc->vertexDescriptor();

        // Create vertex layouts description
        std::vector<BufferLayoutDescriptor> vertexLayoutDescriptors;

        BufferLayoutDescriptor layoutDesc;
        layoutDesc.Stride = 9 * sizeof(float);
        layoutDesc.Attributes.push_back({VertexFormat::Float32x3, 0, 0});
        layoutDesc.Attributes.push_back({VertexFormat::Float32x2, 1, 3 * sizeof(float)});
        layoutDesc.Attributes.push_back({VertexFormat::Float32x4, 2, 5 * sizeof(float)});
        vertexLayoutDescriptors.push_back(layoutDesc);

        // Create vertex buffer layouts
        MetalVertexBufferLayoutAttributesDto dto = MetalUtil::VertexBufferLayout.Create(vertexLayoutDescriptors);

        NS::UInteger i = 0;
        for (auto layout : dto.BufferLayouts)
        {
            pVertexDesc->layouts()->setObject(layout, i);
        }
        i = 0;
        for (auto attr : dto.BufferAttributes)
        {
            pVertexDesc->attributes()->setObject(attr, i);
        }

        // set pixel format
        MTL::RenderPipelineColorAttachmentDescriptor *colorAttachment = pDesc->colorAttachments()->object(NS::UInteger(0));
        colorAttachment->setPixelFormat(MTL::PixelFormat::PixelFormatBGRA8Unorm);

        colorAttachment->setBlendingEnabled(true);

        colorAttachment->setRgbBlendOperation(MTL::BlendOperationAdd);
        colorAttachment->setSourceRGBBlendFactor(MTL::BlendFactorSourceAlpha);
        colorAttachment->setDestinationRGBBlendFactor(MTL::BlendFactorOneMinusSourceAlpha);

        colorAttachment->setAlphaBlendOperation(MTL::BlendOperationAdd);
        colorAttachment->setSourceAlphaBlendFactor(MTL::BlendFactorSourceAlpha);
        colorAttachment->setDestinationAlphaBlendFactor(MTL::BlendFactorOneMinusSourceAlpha);

        m_pipeline = m_device->newRenderPipelineState(pDesc, &pError);
        if (!m_pipeline)
        {
            printf("%s", pError->localizedDescription()->utf8String());
            assert(false);
        }

        // release
        MetalVertexBufferLayoutUtil::DeleteVertexBufferLayouts(dto);
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
    void MetalBasicMeshTexturedTestMaterial::Draw(const Camera &camera, Mesh *mesh)
    {
        MetalMesh *metalMesh = static_cast<MetalMesh *>(mesh);
        MetalTexture2D *texture = static_cast<MetalTexture2D *>(m_texture);

        MTL::RenderCommandEncoder *renderCommandEncoder = m_renderer->GetRenderCommandEncoder();
        renderCommandEncoder->setRenderPipelineState(m_pipeline);
        renderCommandEncoder->setVertexBuffer(metalMesh->VertexBuffer, NS::UInteger(0), NS::UInteger(0));
        renderCommandEncoder->setFragmentTexture(texture->Texture, NS::UInteger(0));
        renderCommandEncoder->setFragmentSamplerState(texture->Sampler, NS::UInteger(0));
        renderCommandEncoder->drawIndexedPrimitives(
            MTL::PrimitiveType::PrimitiveTypeTriangle,
            NS::UInteger(6),
            metalMesh->IndexFormat,
            metalMesh->IndexBuffer,
            NS::UInteger(0));
    }

    /**
     * @brief Render the passed in mesh multiple times.
     * If transform is empty, then the mesh will be ignored.
     * @param camera The camera to render the mesh with.
     * @param mesh The mesh to render.
     * @param transforms The transforms to render the mesh with.
     * @return void
     */
    void MetalBasicMeshTexturedTestMaterial::Draw(const Camera &camera, const Mesh &mesh, std::vector<Mat4x4f> transforms)
    {
        MTL::RenderCommandEncoder *renderCommandEncoder =  m_renderer->GetRenderCommandEncoder();
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
    void MetalBasicMeshTexturedTestMaterial::DrawInstancedPrefilled(const Camera &camera, const Mesh &mesh, f32 *flatTransformsArray, i32 nOfInstances)
    {
        MTL::RenderCommandEncoder *renderCommandEncoder =  m_renderer->GetRenderCommandEncoder();
        renderCommandEncoder->setRenderPipelineState(m_pipeline);
        renderCommandEncoder->drawPrimitives(MTL::PrimitiveType::PrimitiveTypeTriangle, NS::UInteger(0), NS::UInteger(3));
    }

    /**
     * @brief Create a new copy of material
     */
    Material *MetalBasicMeshTexturedTestMaterial::Copy() { return new MetalBasicMeshTexturedTestMaterial(m_framework, m_texture); }
}


#endif // __APPLE__