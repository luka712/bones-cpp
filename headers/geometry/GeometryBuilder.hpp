#ifndef BNS_GEOMETRY_BUILDER_HPP

#define BNS_GEOMETRY_BUILDER_HPP

#include "data/Types.hpp"
#include "geometry/Geometry.hpp"

namespace bns
{
    class GeometryBuilder
    {
    public:
        /**
         * @brief Create a triangle geometry.
        */
        Geometry CreateTriangleGeometry();

        /**
         * @brief Create a quad geometry.
        */
        Geometry CreateQuadGeometry(bool indices = true);
    };
}

#endif // !BNS_GEOMETRY_BUILDER_HPP