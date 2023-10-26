#ifndef BNS_AMBIENT_LIGHT_HPP

#define BNS_AMBIENT_LIGHT_HPP

#include "data/Color.hpp"

namespace bns 
{
    /// @brief The ambient light.
    struct AmbientLight 
    {
        /// @brief The default constructor.
        AmbientLight();

        /// @brief The color of the ambient light.
        Color Color;

        /// @brief The intensity of the ambient light.
        f32 Intensity;

        f32 _Padding[3];
    };
}

#endif 