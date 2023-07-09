#include "mesh/wgpu/WebGPUMesh.hpp"
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

        IndicesBuffer = InitializeIndicesBuffer();
        VertexPositionsBuffer = InitializeVertexPositionsBuffer();
        VertexColorsBuffer = InitializeVertexColorsBuffer();
    }

    void WebGPUMesh::Delete()
    {
        Mesh::Delete();
        wgpuBufferDestroy(IndicesBuffer);
        wgpuBufferDestroy(VertexPositionsBuffer);
        wgpuBufferDestroy(VertexColorsBuffer);
    }

    WGPUBuffer WebGPUMesh::InitializeIndicesBuffer()
    {
        size_t byteSize = m_geometry.Indices.size() * sizeof(u32);

        WGPUBufferDescriptor bufferDescriptor = {};
        bufferDescriptor.label = "index_buffer";
        bufferDescriptor.size = byteSize;
        bufferDescriptor.usage = WGPUBufferUsage_Index;
        bufferDescriptor.mappedAtCreation = true;
        bufferDescriptor.nextInChain = nullptr;
        WGPUBuffer buffer = wgpuDeviceCreateBuffer(m_device, &bufferDescriptor);

        IndexFormat = WGPUIndexFormat_Uint32;

        /*
                void *mappedRange = wgpuBufferGetMappedRange(buffer, 0, byteSize);
                WGPUBufferMapCallback cb = [](WGPUBufferMapAsyncStatus status, void *userData)
                {
                    if (status == WGPUBufferMapAsyncStatus_Success)
                    {
                        MappedRangeData<u32> *tempUserData = static_cast<MappedRangeData<u32> *>(userData);
                        memcpy(tempUserData->MappedRange, tempUserData->Indices.data(), tempUserData->ByteSize);
                        wgpuBufferUnmap(tempUserData->Buffer);
                    }
                };

                MappedRangeData<u32> userData;
                userData.MappedRange = mappedRange;
                userData.Indices = m_geometry.Indices;
                userData.ByteSize = byteSize;
                userData.Buffer = buffer;
                wgpuBufferMapAsync(buffer, WGPUMapMode_Write, 0, byteSize, cb, &userData);
                */

        memcpy(wgpuBufferGetMappedRange(buffer, 0, byteSize), m_geometry.Indices.data(), byteSize);
        wgpuBufferUnmap(buffer);
        return buffer;
    }

    WGPUBuffer WebGPUMesh::InitializeVertexPositionsBuffer()
    {
        size_t byteSize = m_geometry.VertexPositions.size() * sizeof(f32);

        WGPUBufferDescriptor bufferDescriptor = {};
        bufferDescriptor.label = "vertex_positions_buffer";
        bufferDescriptor.size = byteSize;
        bufferDescriptor.usage = WGPUBufferUsage_Vertex;
        bufferDescriptor.mappedAtCreation = true;
        bufferDescriptor.nextInChain = nullptr;
        WGPUBuffer buffer = wgpuDeviceCreateBuffer(m_device, &bufferDescriptor);

        memcpy(wgpuBufferGetMappedRange(buffer, 0, byteSize), m_geometry.VertexPositions.data(), byteSize);
        wgpuBufferUnmap(buffer);

        VertexPositionsBuffer = buffer;
        VertexPositionsBufferSize = byteSize;

        return buffer;
    }

    WGPUBuffer WebGPUMesh::InitializeVertexColorsBuffer()
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

        size_t byteSize = colors.size() * sizeof(f32);

        WGPUBufferDescriptor bufferDescriptor = {};
        bufferDescriptor.label = "vertex_colors_buffer";
        bufferDescriptor.size = byteSize;
        bufferDescriptor.usage = WGPUBufferUsage_Vertex;
        bufferDescriptor.mappedAtCreation = true;
        bufferDescriptor.nextInChain = nullptr;
        WGPUBuffer buffer = wgpuDeviceCreateBuffer(m_device, &bufferDescriptor);

        memcpy(wgpuBufferGetMappedRange(buffer, 0, byteSize), colors.data(), byteSize);
        wgpuBufferUnmap(buffer);

        VertexColorsBuffer = buffer;
        VertexColorsBufferSize = byteSize;

        return buffer;
    }

}
