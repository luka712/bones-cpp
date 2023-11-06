#ifdef __APPLE__

#ifndef BNS_METAL_MESH_HPP

#define BNS_METAL_MESH_HPP

#include "BnsMetal.hpp"
#include "mesh/Mesh.hpp"
#include "geometry/Geometry.hpp"
#include "renderer/MetalRenderer.hpp"

namespace bns
{
    class MetalMesh final : public Mesh
    {

    private:
        MetalRenderer* m_renderer;

        MTL::Device *m_device;

        size_t m_numOfVertices;

        const Geometry &m_geometry;

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
        MetalMesh(const Framework &framework, const Geometry &geometry);

        MTL::Buffer *IndexBuffer;
        MTL::IndexType IndexFormat;

        MTL::Buffer *VertexBuffer;
        size_t VertexBufferSize;

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

#endif // __APPLE__