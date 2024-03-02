#ifndef BNS_MATH_H

#define BNS_MATH_H

#include "bns_types.hpp"
#include "math/bns_vec2.hpp"
#include "bns_color.hpp"

namespace bns
{
    /// @brief Convert degrees to radians.
    /// @param degrees The degrees to convert.
    inline f32 ToRadians(f32 degrees) 
    {
        return degrees * (PI / 180.0f);
    }
}

#endif