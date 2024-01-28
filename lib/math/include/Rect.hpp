#ifndef BNS_RECT_HPP

#define BNS_RECT_HPP

#include "Types.hpp"

namespace bns
{
    /// @brief The rectangle.
    struct Rect
    {
        f32 X;
        f32 Y;
        f32 Width;
        f32 Height;

        /// @brief The default constructor.
        Rect();

        /// @brief The constructor.
        /// @param x The x coordinate.
        /// @param y The y coordinate.
        /// @param width The width.
        /// @param height The height.
        Rect(f32 x, f32 y, f32 width, f32 height);
    };
}

#endif