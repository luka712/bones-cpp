#include "mesh/metal/MetalMesh.hpp"
#include "Framework.hpp"
#include "data/Types.hpp"
#include "util/metal/MetalBufferUtil.hpp"

namespace bns
{

    MetalMesh::MetalMesh(const Framework &framework, const Geometry &geometry)
        : Mesh(framework), m_geometry(geometry)
    {
        m_numOfVertices = geometry.VertexPositions.size() / 3UL;
        IndicesCount = geometry.Indices.size();
    }

    void MetalMesh::Initialize()
    {
        m_device = m_framework.Context.MetalDevice;

        // IndicesBuffer = InitializeIndicesBuffer();
        VertexPositionsBuffer = InitializeVertexPositionsBuffer();
        VertexColorsBuffer = InitializeVertexColorsBuffer();
        TextureCoordsBuffer = InitializeTextureCoordinatesBuffer();
    }

    void MetalMesh::Delete()
    {
        Mesh::Delete();
        VertexPositionsBuffer->release();
        VertexColorsBuffer->release();
        TextureCoordsBuffer->release();
    }

    MTL::Buffer *MetalMesh::InitializeVertexPositionsBuffer()
    {
        MTL::Device *device = m_framework.Context.MetalDevice;
        MTL::Buffer *buffer = MetalBufferUtil::CreateVertexBuffer(device,
                                                                  m_geometry.VertexPositions,
                                                                  "VertexPositionsBuffer");
        return buffer;
    }

    MTL::Buffer *MetalMesh::InitializeVertexColorsBuffer()
    {
        std::vector<f32> colors = m_geometry.VertexColors;

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

        MTL::Device *device = m_framework.Context.MetalDevice;

        MTL::Buffer *buffer = MetalBufferUtil::CreateVertexBuffer(device,
                                                                  colors,
                                                                  "VertexColorsBuffer");

        return buffer;
    }

    MTL::Buffer* MetalMesh::InitializeTextureCoordinatesBuffer()
    {
        std::vector<f32> texCoords = m_geometry.TextureCoordinates;
        MTL::Device *device = m_framework.Context.MetalDevice;
        MTL::Buffer* buffer = MetalBufferUtil::CreateVertexBuffer(device,
                                                                  texCoords,
                                                                  "TextureCoordinatesBuffer");
        
        return buffer;
    }

}
