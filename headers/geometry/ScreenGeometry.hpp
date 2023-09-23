#ifndef BNS_SCREEN_GEOMETRY_HPP

#define BNS_SCREEN_GEOMETRY_HPP

#include "geometry/Geometry.hpp"
namespace bns
{
    /**
     * Geometry that is used to cover screen area. It is used for post processing.
    */
    struct ScreenGeometry : public Geometry
    {
        ScreenGeometry();
    };
}

#endif
