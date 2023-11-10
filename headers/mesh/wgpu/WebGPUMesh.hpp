#ifndef BNS_WEBGPU_MESH_HPP

#define BNS_WEBGPU_MESH_HPP

#include "mesh/Mesh.hpp"
#include <webgpu/webgpu.h>
#include "geometry/Geometry.hpp"
#include "renderer/WebGPURenderer.hpp"

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
        /// @brief The renderer
        WebGPURenderer *m_renderer;

        WGPUDevice m_device;

        size_t m_numOfVertices;

        const Geometry &m_geometry;

        /**
         * @brief Initialize the indices buffer.
         */
        void InitializeIndicesBuffer();

        /**
         * @brief Initialize the vertex buffer.
         * Vertex buffer is used when buffer is interleaved.
        */
        void InitializeVertexBuffer();

        /**
         * @brief Initialize the vertex positions buffer.
         */
        void InitializeVertexPositionsBuffer();

        /**
         * @brief Initialize the vertex colors buffer.
         */
        void InitializeVertexColorsBuffer();

        /**
         * @brief Initialize the texture coordinates buffer.
        */
        void InitializeTextureCoordinatesBuffer();

    public:
        WebGPUMesh(const Framework &framework, const Geometry &geometry);

        WGPUBuffer IndexBuffer;
        WGPUIndexFormat IndexFormat;

        WGPUBuffer VertexBuffer;
        size_t VertexBufferSize;

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
