#include "math/bns_rect.hpp"

namespace bns
{
    Rect::Rect()
        : X(0), Y(0), Width(0), Height(0)
    {
    }

    Rect::Rect(f32 x, f32 y, f32 width, f32 height)
        : X(x), Y(y), Width(width), Height(height)
    {
    }
}