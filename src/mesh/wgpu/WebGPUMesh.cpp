#include "mesh/wgpu/WebGPUMesh.hpp"
#include "util/wgpu/WebGPUBufferUtil.hpp"
#include "Framework.hpp"

namespace bns
{
    WebGPUMesh::WebGPUMesh(const Framework &framework, const Geometry &geometry)
        : Mesh(framework), m_geometry(geometry)
    {
        m_numOfVertices = geometry.VertexPositions.size() / 3UL;
        IndicesCount = geometry.Indices.size();
    }

    void WebGPUMesh::Initialize()
    {
        m_device = m_framework.Context.WebGPUDevice;

        InitializeIndicesBuffer();
        InitializeVertexPositionsBuffer();
        InitializeVertexColorsBuffer();
        InitializeTextureCoordinatesBuffer();
    }

    void WebGPUMesh::Delete()
    {
        Mesh::Delete();
        wgpuBufferDestroy(IndicesBuffer);
        wgpuBufferDestroy(VertexPositionsBuffer);
        wgpuBufferDestroy(VertexColorsBuffer);
    }

    void WebGPUMesh::InitializeIndicesBuffer()
    {
        // byteSize is the size of the buffer in bytes, which is the number of indices * the size of an type of element.
        // to get type use the type of the first element in the vector
        size_t elementSize = 4;
        if (!m_geometry.Indices.empty())
        {
            elementSize = sizeof(m_geometry.Indices[0]);

            IndicesBuffer = WebGPUBufferUtil::CreateIndexBuffer(m_device, m_geometry.Indices, "index_buffer");

            IndexFormat = WGPUIndexFormat_Uint32;
            if (elementSize == 2)
            {
                IndexFormat = WGPUIndexFormat_Uint16;
            }
        }
    }

    void WebGPUMesh::InitializeVertexPositionsBuffer()
    {
        if (m_geometry.VertexPositions.empty())
        {
            return;
        }

        size_t byteSize = m_geometry.VertexPositions.size() * sizeof(f32);
        VertexPositionsBuffer = WebGPUBufferUtil::CreateVertexBuffer(m_device, m_geometry.VertexPositions, "vertex_positions_buffer");
        VertexPositionsBufferSize = byteSize;
    }

    void WebGPUMesh::InitializeTextureCoordinatesBuffer()
    {
        if (m_geometry.TextureCoordinates.empty())
        {
            return;
        }

        size_t byteSize = m_geometry.TextureCoordinates.size() * sizeof(f32);
        TextureCoordinatesBuffer = WebGPUBufferUtil::CreateVertexBuffer(m_device, m_geometry.TextureCoordinates, "texture_coordinates_buffer");
        TextureCoordinatesBufferSize = byteSize;
    }

    void WebGPUMesh::InitializeVertexColorsBuffer()
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

        if (colors.empty())
        {
            return;
        }

        size_t byteSize = colors.size() * sizeof(f32);
        VertexColorsBuffer = WebGPUBufferUtil::CreateVertexBuffer(m_device, colors, "vertex_colors_buffer");
        VertexColorsBufferSize = byteSize;
    }

}
