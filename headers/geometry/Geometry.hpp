#ifndef BNS_GEOMETRY_HPP

#define BNS_GEOMETRY_HPP

#include "data/Types.hpp"
#include <vector>

namespace bns
{
    struct Geometry
    {

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
