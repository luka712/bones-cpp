#ifndef BNS_COLOR_HPP

#define BNS_COLOR_HPP

#include "Types.hpp"

namespace bns 
{
       /**
     * @brief
     * Color with floating point values between 0.0f and 1.0f ideally.
     */
    struct Color
    {
        f32 R;
        f32 G;
        f32 B;
        f32 A;

        /**
         * @brief Construct a new Color F object
         *
         * @param r
         * @param g
         * @param b
         * @param a
         */
        Color(f32 r, f32 g, f32 b, f32 a)
        {
            R = r;
            G = g;
            B = b;
            A = a;
        }

        /**
         * @brief Construct a new Color F object
         *
         * @param r
         * @param g
         * @param b
         */
        Color(f32 r, f32 g, f32 b)
            : Color(r, g, b, 1.0)
        {
        }

        /**
         * @brief Construct a new Color F object
         */
        Color()
            : Color(1.0, 1.0, 1.0, 1.0) {}

        /**
         * @brief Returns the light pink color.
         *
         * @return Color
         */
        static Color LightPink()
        {
            return Color(1.0f, 0.71f, 0.76f);
        }

        /**
         * @brief Returns the light gray color.
         *
         * @return Color
         */
        static Color LightGray()
        {
            return Color(0.83f, 0.83f, 0.83f);
        }

        /**
         * @brief Returns the grayish blue color.
         *
         * @return Color
         */
        static Color GrayishBlue()
        {
            return Color(163.0f / 255.0f, 167.0f / 255.0f, 194.0f / 255.0f);
        }

        /**
         * @brief Returns the white color.
         *
         * @return Color
         */
        static Color White()
        {
            return Color(1.0f, 1.0f, 1.0f);
        }

        /**
         * @brief Returns the black color.
         *
         * @return Color
         */
        static Color Black()
        {
            return Color(0.0f, 0.0f, 0.0f);
        }

        /**
         * @brief Returns the yellow color.
         *
         * @return Color
         */
        static Color Yellow()
        {
            return Color(1.0f, 1.0f, 0.0f);
        }

        /**
         * @brief Returns the red color.
         *
         * @return Color
         */
        static Color Red()
        {
            return Color(1.0f, 0.0f, 0.0f);
        }

        /**
         * @brief Returns the blue color.
         *
         * @return Color
         */
        static Color Blue()
        {
            return Color(0.0f, 0.0f, 1.0f);
        }
    };
}

#endif 