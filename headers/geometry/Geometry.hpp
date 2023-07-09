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
         * @brief The indices of a mesh.
         */
        std::vector<u32> Indices;

        /**
         * @brief The vertex colors of the mesh.
         */
        std::vector<f32> VertexColors;
    };
}

#endif