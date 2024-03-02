#ifndef BNS_POINT_LIGHT_HPP

#define BNS_POINT_LIGHT_HPP

#include "bns_color.hpp"
#include "math/bns_vec3.hpp"

namespace bns
{
    /// @brief The attenuation of the point light.
    /// @details The attenuation is used to calculate the intensity of the light.
    /// it is calculated as unit / (constant + linear * d + quadratic * d * d)
    /// where d is the distance between the light and the fragment.
    struct Attenuation
    {
        /// @brief The unit of the attenuation.
        f32 Unit;

        /// @brief The constant of the attenuation.
        f32 Constant;

        /// @brief The linear of the attenuation.
        f32 Linear;

        /// @brief The quadratic of the attenuation.
        f32 Quadratic;

        /// @brief  The default constructor.
        Attenuation();

        /// @brief The calculation of the attenuation when the distance is given.
        /// @param distance The distance, usually the distance between the light and the fragment.
        /// @return The attenuation.
        f32 GetAttenuation(const f32 distance);

        /// @brief Prepare the attenuation with 100 unit. Usually fit for 2d distance when using lights for sprites.
        /// This is using 100 as the unit since 2d distances are usually large.
        /// @return The attenuation.
        static Attenuation AsSpriteLight();
    };

    /// @brief The point light.
    struct PointLight
    {
        /// @brief The default constructor.
        PointLight();

        /// @brief The color of the point light.
        Color Color; // 16b

        /// @brief The position of the point light.
        Vec3f Position; 

        /// @brief The intensity of the point light.
        f32 Intensity; 

        /// @brief The attenuation of the point light.
        Attenuation Attenuation; 

        /// @brief Prepares the lights to be used for sprites.
        /// Marked by large attenuation unit (100 unit) since 2d distances are usually large.
        /// Z is set to 100 to make sure the light is in front of the sprite and quite far ( so that large are is lit).
        /// @return The point light.
        static PointLight AsSpriteLight();
    };
}

#endif
