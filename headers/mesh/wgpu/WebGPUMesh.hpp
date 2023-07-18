#ifndef BNS_WEBGPU_MESH_HPP

#define BNS_WEBGPU_MESH_HPP

#include "mesh/Mesh.hpp"
#include <webgpu/webgpu.h>
#include "geometry/Geometry.hpp"

namespace bns
{
    class Framework;

    template <typename T>
    struct MappedRangeData
    {
        void *MappedRange;
        std::vector<T> Indices;
        size_t ByteSize;
        WGPUBuffer Buffer;
    };

    class WebGPUMesh final : public Mesh
    {

    private:
        WGPUDevice m_device;

        size_t m_numOfVertices;

        const Geometry &m_geometry;

        /**
         * @brief Initialize the indices buffer.
         */
        WGPUBuffer InitializeIndicesBuffer();

        /**
         * @brief Initialize the vertex positions buffer.
         */
        WGPUBuffer InitializeVertexPositionsBuffer();

        /**
         * @brief Initialize the vertex colors buffer.
         */
        WGPUBuffer InitializeVertexColorsBuffer();

        /**
         * @brief Initialize the texture coordinates buffer.
        */
        WGPUBuffer InitializeTextureCoordinatesBuffer();

    public:
        WebGPUMesh(const Framework &framework, const Geometry &geometry);

        WGPUBuffer IndicesBuffer;
        WGPUIndexFormat IndexFormat;

        WGPUBuffer VertexPositionsBuffer;
        size_t VertexPositionsBufferSize;

        WGPUBuffer VertexColorsBuffer;
        size_t VertexColorsBufferSize;

        WGPUBuffer TextureCoordinatesBuffer;
        size_t TextureCoordinatesBufferSize;

        /**
         * @brief Initialize the mesh
         */
        void Initialize() override;

        /**
         * @brief Delete the mesh
         */
        void Delete() override;
    };
}

#endif
