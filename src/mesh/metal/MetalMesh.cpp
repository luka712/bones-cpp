#include "mesh/metal/MetalMesh.hpp"
#include "Framework.hpp"
#include "data/Types.hpp"

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
    }

    void MetalMesh::Delete()
    {
        Mesh::Delete();
        VertexPositionsBuffer->release();
        VertexColorsBuffer->release();
    }

    MTL::Buffer *MetalMesh::InitializeVertexPositionsBuffer()
    {
        MTL::Device *device = m_framework.Context.MetalDevice;
        size_t byteSize = 16 * m_numOfVertices;

        float *data = new float[m_numOfVertices * 4];
        if (m_geometry.VertexPositionsStride == 12)
        {
            for (size_t i = 0; i < m_numOfVertices; i++)
            {
                data[i * 4 + 0] = m_geometry.VertexPositions[i * 3 + 0];
                data[i * 4 + 1] = m_geometry.VertexPositions[i * 3 + 1];
                data[i * 4 + 2] = m_geometry.VertexPositions[i * 3 + 2];
                data[i * 4 + 3] = 1.0f;
            }
        }
        else
        {
            for (size_t i = 0; i < m_numOfVertices; i++)
            {
                data[i * 4 + 0] = m_geometry.VertexPositions[i * 4 + 0];
                data[i * 4 + 1] = m_geometry.VertexPositions[i * 4 + 1];
                data[i * 4 + 2] = m_geometry.VertexPositions[i * 4 + 2];
                data[i * 4 + 3] = m_geometry.VertexPositions[i * 4 + 3];
            }
        }

        MTL::Buffer *buffer = device->newBuffer(data,
                                                byteSize,
                                                MTL::ResourceOptionCPUCacheModeDefault);

        delete[] data;

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
        size_t byteSize = colors.size() * sizeof(f32);

        MTL::Buffer *buffer = device->newBuffer(colors.data(),
                                                byteSize,
                                                MTL::ResourceOptionCPUCacheModeDefault);

        return buffer;
    }

}
