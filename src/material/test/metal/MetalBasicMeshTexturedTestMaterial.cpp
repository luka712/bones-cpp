#include "Framework.hpp"
#include "mesh/metal/MetalMesh.hpp"
#include "material/test/metal/MetalBasicMeshTexturedTestMaterial.hpp"
#include "renderer/common/MetalRenderPipelineUtil.hpp"
#include "textures/metal/MetalTexture2D.hpp"

namespace bns
{
    MetalBasicMeshTexturedTestMaterial::MetalBasicMeshTexturedTestMaterial(Framework &framework, Texture2D *texture)
        : m_framework(framework), m_texture(texture)
    {
    }

    MetalBasicMeshTexturedTestMaterial::~MetalBasicMeshTexturedTestMaterial()
    {
    }

    void MetalBasicMeshTexturedTestMaterial::Initialize()
    {
        std::string shaderSource = m_framework.FileLoader.OpenFile("shaders/metal/basic_mesh_textured_test_shader.metal");

        MTL::Device *device = m_framework.Context.MetalDevice;

        NS::Error *pError = nullptr;
        NS::String *pSource = NS::String::string(shaderSource.c_str(), NS::StringEncoding::UTF8StringEncoding);
        MTL::Library *pLibrary = device->newLibrary(pSource, nullptr, &pError);
        if (!pLibrary)
        {
            printf("%s", pError->localizedDescription()->utf8String());
            assert(false);
        }

        MTL::Function *pVertexFn = pLibrary->newFunction(NS::String::string("vs_main", NS::StringEncoding::UTF8StringEncoding));
        MTL::Function *pFragFn = pLibrary->newFunction(NS::String::string("fs_main", NS::StringEncoding::UTF8StringEncoding));

        MTL::RenderPipelineDescriptor *pDesc = MetalRenderPipelineUtil::CreatePipelineDescriptor(pVertexFn, pFragFn);
        
        // Setup blending

        // vertex
        MTL::VertexDescriptor *pVertexDesc = pDesc->vertexDescriptor();

        // position layout
        MTL::VertexBufferLayoutDescriptor *pPositionLayoutDesc = MTL::VertexBufferLayoutDescriptor::alloc();
        pPositionLayoutDesc->setStride(NS::UInteger(3 * sizeof(float)));
        pPositionLayoutDesc->setStepFunction(MTL::VertexStepFunction::VertexStepFunctionPerVertex);
        pPositionLayoutDesc->setStepRate(NS::UInteger(1));
        pVertexDesc->layouts()->setObject(pPositionLayoutDesc, 0);

        // position attribute
        MTL::VertexAttributeDescriptor *pPositionAttrDescriptor = MTL::VertexAttributeDescriptor::alloc();
        pPositionAttrDescriptor->setFormat(MTL::VertexFormatFloat3);
        pPositionAttrDescriptor->setOffset(NS::UInteger(0));
        pPositionAttrDescriptor->setBufferIndex(NS::UInteger(0));
        pVertexDesc->attributes()->setObject(pPositionAttrDescriptor, 0);

        // color layout
        MTL::VertexBufferLayoutDescriptor *pColorLayoutDesc = MTL::VertexBufferLayoutDescriptor::alloc();
        pColorLayoutDesc->setStride(NS::UInteger(4 * sizeof(float)));
        pColorLayoutDesc->setStepFunction(MTL::VertexStepFunction::VertexStepFunctionPerVertex);
        pColorLayoutDesc->setStepRate(NS::UInteger(1));
        pVertexDesc->layouts()->setObject(pColorLayoutDesc, 1);

        // color attribute
        MTL::VertexAttributeDescriptor *pColorAttrDescriptor = MTL::VertexAttributeDescriptor::alloc();
        pColorAttrDescriptor->setFormat(MTL::VertexFormatFloat4);
        pColorAttrDescriptor->setOffset(NS::UInteger(0));
        pColorAttrDescriptor->setBufferIndex(NS::UInteger(1));
        pVertexDesc->attributes()->setObject(pColorAttrDescriptor, 1);

        // texture layout
        MTL::VertexBufferLayoutDescriptor *pTextureLayoutDesc = MTL::VertexBufferLayoutDescriptor::alloc();
        pTextureLayoutDesc->setStride(NS::UInteger(2 * sizeof(float)));
        pTextureLayoutDesc->setStepFunction(MTL::VertexStepFunction::VertexStepFunctionPerVertex);
        pTextureLayoutDesc->setStepRate(NS::UInteger(1));
        pVertexDesc->layouts()->setObject(pTextureLayoutDesc, 2);

        // texture attribute
        MTL::VertexAttributeDescriptor *pTextureAttrDescriptor = MTL::VertexAttributeDescriptor::alloc();
        pTextureAttrDescriptor->setFormat(MTL::VertexFormatFloat2);
        pTextureAttrDescriptor->setOffset(NS::UInteger(0));
        pTextureAttrDescriptor->setBufferIndex(NS::UInteger(2));
        pVertexDesc->attributes()->setObject(pTextureAttrDescriptor, 2);

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

        m_pipeline = device->newRenderPipelineState(pDesc, &pError);
        if (!m_pipeline)
        {
            printf("%s", pError->localizedDescription()->utf8String());
            assert(false);
        }

        pPositionAttrDescriptor->release();
        pPositionLayoutDesc->release();
        pColorAttrDescriptor->release();
        pColorLayoutDesc->release();
        pTextureAttrDescriptor->release();
        pTextureLayoutDesc->release();
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

        MTL::RenderCommandEncoder *renderCommandEncoder = m_framework.Context.CurrentMetalRenderCommandEncoder;
        renderCommandEncoder->setRenderPipelineState(m_pipeline);
        renderCommandEncoder->setVertexBuffer(metalMesh->VertexPositionsBuffer, NS::UInteger(0), NS::UInteger(0));
        renderCommandEncoder->setVertexBuffer(metalMesh->VertexColorsBuffer, NS::UInteger(0), NS::UInteger(1));
        renderCommandEncoder->setVertexBuffer(metalMesh->TextureCoordsBuffer, NS::UInteger(0), NS::UInteger(2));
        renderCommandEncoder->setFragmentTexture(texture->Texture, NS::UInteger(0));
        renderCommandEncoder->setFragmentSamplerState(texture->Sampler, NS::UInteger(0));
        renderCommandEncoder->drawPrimitives(MTL::PrimitiveType::PrimitiveTypeTriangle, NS::UInteger(0), NS::UInteger(6));
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
        MTL::RenderCommandEncoder *renderCommandEncoder = m_framework.Context.CurrentMetalRenderCommandEncoder;
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
        MTL::RenderCommandEncoder *renderCommandEncoder = m_framework.Context.CurrentMetalRenderCommandEncoder;
        renderCommandEncoder->setRenderPipelineState(m_pipeline);
        renderCommandEncoder->drawPrimitives(MTL::PrimitiveType::PrimitiveTypeTriangle, NS::UInteger(0), NS::UInteger(3));
    }

    /**
     * @brief Create a new copy of material
     */
    Material *MetalBasicMeshTexturedTestMaterial::Copy() { return new MetalBasicMeshTexturedTestMaterial(m_framework, m_texture); }
}
