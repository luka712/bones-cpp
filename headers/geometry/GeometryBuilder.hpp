#ifndef BNS_GEOMETRY_BUILDER_HPP

#define BNS_GEOMETRY_BUILDER_HPP

#include "data/Types.hpp"
#include "geometry/Geometry.hpp"

namespace bns
{
    class GeometryBuilder final
    {
    public:
        /**
         * @brief Create a triangle geometry.
        */
        Geometry CreateTriangleGeometry();

        /**
         * @brief Create a quad geometry.
        */
        Geometry CreateQuadGeometry();

        /**
         * @brief Create an interleaved geometry.
        */
        Geometry CreateInterleavedQuadGeometry();
    };
}

#endif // !BNS_GEOMETRY_BUILDER_HPP