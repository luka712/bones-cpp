#ifndef BNS_RECT_HPP

#define BNS_RECT_HPP

#include "data/Types.hpp"

namespace bns
{
    struct Rect
    {
        i32 X;
        i32 Y;
        i32 Width;
        i32 Height;

        /**
         * The constructor.
         */
        Rect() : X(0), Y(0), Width(0), Height(0)
        {
        }

        Rect(i32 x, i32 y, i32 width, i32 height) 
            : X(x), Y(y), Width(width), Height(height)
        {
        }
    };
}

#endif