#ifndef BNS_METAL_MESH_HPP

#define BNS_METAL_MESH_HPP

#include <Metal/Metal.hpp>
#include "mesh/Mesh.hpp"
#include "geometry/Geometry.hpp"

namespace bns
{
    class MetalMesh final : public Mesh
    {

    private:
        MTL::Device *m_device;

        size_t m_numOfVertices;

        const Geometry &m_geometry;

        /**
         * @brief Initialize the indices buffer.
         */
        MTL::Buffer *InitializeIndicesBuffer();

        /**
         * @brief Initialize the vertex positions buffer.
         */
        MTL::Buffer *InitializeVertexPositionsBuffer();

        /**
         * @brief Initialize the vertex colors buffer.
         */
        MTL::Buffer *InitializeVertexColorsBuffer();
        
        /**
         * @brief Initialize the texture coordinates buffer.
        */
        MTL::Buffer* InitializeTextureCoordinatesBuffer();

    public:
        MetalMesh(const Framework &framework, const Geometry &geometry);

        // WGPUBuffer IndicesBuffer;
        // WGPUIndexFormat IndexFormat;

        MTL::Buffer *VertexPositionsBuffer;
        size_t VertexPositionsBufferSize;

        MTL::Buffer *VertexColorsBuffer;
        size_t VertexColorsBufferSize;
        
        MTL::Buffer *TextureCoordsBuffer;
        size_t TextureCoordsBufferSize;

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
