#ifndef BNS_GEOMETRY_BUILDER_HPP

#define BNS_GEOMETRY_BUILDER_HPP

#include "geometry/bns_geometry.hpp"

namespace bns
{
    /// @brief The geometry builder.
    class GeometryBuilder
    {
    public:

        /// @brief Creates a quad geometry.
        /// @return The quad geometry.
        Geometry QuadGeomtry();

        /// @brief Creates a cube geometry.
        /// @return The cube geometry.
        Geometry CubeGeometry();
    };
}

#endif