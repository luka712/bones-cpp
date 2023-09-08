#ifndef BNS_QUAD_HPP

#define BNS_QUAD_HPP

#include "data/Vec2.hpp"

namespace bns
{
    struct Quad final
    {
        Vec2f TopLeft;
        Vec2f TopRight;
        Vec2f BottomRight;
        Vec2f BottomLeft;
    };
}

#endif // !BNS_QUAD_HPP