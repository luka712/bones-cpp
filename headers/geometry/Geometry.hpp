#ifndef BNS_GEOMETRY_HPP

#define BNS_GEOMETRY_HPP

#include "data/Types.hpp"
#include <vector>

namespace bns
{
    struct GeometryAttributes
    {
        /**
         * @brief The offset compared to previous attribute.
         */
        size_t Offset;

        /**
         * @brief The size of the attribute.
         * Usually 1 for float, 2 for vec2, 3 for vec3, 4 for vec4 ... etc.
         */
        size_t Size;
    };

    struct Geometry
    {
        /**
         * The number of vertices.
        */
        size_t NumOfVertices;

        /**
         * @brief The data of the mesh in case if interleaved.
         */
        std::vector<f32> Data;

        /**
         * @brief The stride of the mesh in case if interleaved is used.
        */
        size_t Stride;

        /**
         * @brief The attributes of the geometry.
         */
        std::vector<GeometryAttributes> Attributes;

        bool IsInterleaved;

        /**
         * @brief The vertex positions of the mesh.
         */
        std::vector<f32> VertexPositions;

        /**
         * @brief The stride of the vertex positions.
         */
        size_t VertexPositionsStride;

        /**
         * @brief The indices of a mesh.
         */
        std::vector<u32> Indices;

        /**
         * @brief The texture coordinates of the mesh.
         */
        std::vector<f32> TextureCoordinates;

        /**
         * @brief The stride of the texture coordinates.
         */
        size_t TextureCoordinatesStride;

        /**
         * @brief The vertex colors of the mesh.
         */
        std::vector<f32> VertexColors;

        /**
         * @brief The stride of the vertex colors.
         */
        size_t VertexColorsStride;
    };
}

#endif
