#include "lights/AmbientLight.hpp"

namespace bns
{
    AmbientLight::AmbientLight()
        : Color(Color::White()), Intensity(1.0f)
    {
    }
}