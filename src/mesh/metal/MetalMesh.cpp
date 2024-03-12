#if USE_METAL

#include "mesh/metal/MetalMesh.hpp"
#include "bns_framework.hpp"
#include "bns_types.hpp"
#include "bns_metal_util.hpp"

namespace bns
{

    MetalMesh::MetalMesh(const Framework &framework, const Geometry &geometry)
        : Mesh(framework), m_geometry(geometry)
    {
        m_renderer = static_cast<MetalRenderer *>(framework.GetRenderer());
        // m_numOfVertices = geometry.NumOfVertices;
        IndicesCount = geometry.Indices.size();
        IndexBuffer = nullptr;
        VertexBuffer = nullptr;
        VertexPositionsBuffer = nullptr;
        VertexColorsBuffer = nullptr;
        TextureCoordsBuffer = nullptr;
    }

    void MetalMesh::Initialize()
    {
        m_device = m_renderer->GetDevice();

        if (m_geometry.Indices.size() > 0)
        {
            std::vector<u16> indices = m_geometry.Indices;
            IndexBuffer = MetalUtil::Buffer.CreateIndexBuffer(m_device, indices, "IndexBuffer");
            
            IndexFormat = MTL::IndexTypeUInt32;
            if(sizeof(m_geometry.Indices[0]) == 2)
            {
                IndexFormat = MTL::IndexTypeUInt16;
            }
        }

        /*
        if (m_geometry.IsInterleaved)
        {
            VertexBuffer = MetalUtil::Buffer.Create(m_device, m_geometry.Data, "VertexBuffer");
        }
        else
        {

            InitializeVertexPositionsBuffer();
            InitializeVertexColorsBuffer();
            InitializeTextureCoordinatesBuffer();
        }*/
    }

    void MetalMesh::Delete()
    {
        Mesh::Delete();
        VertexPositionsBuffer->release();
        VertexColorsBuffer->release();
        TextureCoordsBuffer->release();
    }

    void MetalMesh::InitializeVertexPositionsBuffer()
    {
        /*
        IndexBuffer = MetalBufferUtil::Create(m_device,
                                                    m_geometry.VertexPositions,
                                                    "VertexPositionsBuffer");
         */
    }

    void MetalMesh::InitializeVertexColorsBuffer()
    {
        std::vector<f32> colors = m_geometry.Colors;

        // if empty initialize all to white
        if (colors.empty())
        {
            for (size_t i = 0; i < m_numOfVertices; i++)
            {
                colors.push_back(1.0f);
                colors.push_back(1.0f);
                colors.push_back(1.0f);
                colors.push_back(1.0f);
            }
        }

        VertexColorsBuffer = MetalUtil::Buffer.CreateVertexBuffer(m_device,
                                                           colors,
                                                           "VertexColorsBuffer");
    }

    void MetalMesh::InitializeTextureCoordinatesBuffer()
    {
        std::vector<f32> texCoords = m_geometry.TextureCoords;
        MTL::Buffer *buffer = MetalUtil::Buffer.CreateVertexBuffer(m_device,
                                                            texCoords,
                                                            "TextureCoordinatesBuffer");
        TextureCoordsBuffer = buffer;
    }

}

#endif // __APPLE__
