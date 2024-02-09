#ifndef BNS_MATH_H

#define BNS_MATH_H

#include "bns_types.hpp"
#include "Vec2.hpp"
#include "Color.hpp"

namespace bns
{
    /**
     * @brief Convert degrees to radians.
     */
    inline f32 ToRadians(f32 degrees) 
    {
        return degrees * (PI / 180.0f);
    }
}

#endif