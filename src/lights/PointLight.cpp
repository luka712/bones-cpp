#include "lights/PointLight.hpp"

namespace bns
{
    Attenuation::Attenuation()
        : Unit(1.0f), Constant(1.0f), Linear(0.09f), Quadratic(0.0032f)
    {
    }

    f32 Attenuation::GetAttenuation(const f32 distance)
    {
        return Unit / (Constant + Linear * distance + Quadratic * distance * distance);
    }

    Attenuation Attenuation::AsSpriteLight()
    {
        Attenuation attenuation;
        attenuation.Unit = 100.0f;
        attenuation.Constant = 1.0f;
        attenuation.Linear = 0.09f;
        attenuation.Quadratic = 0.0032f;
        return attenuation;
    }

    PointLight::PointLight()
        : Color(Color::Black()),  Position(Vec3f(0.0f, 0.0f, 0.0f)), Intensity(0.0f)
    {
    }

    PointLight PointLight::AsSpriteLight()
    {
        PointLight pointLight;
        pointLight.Color = Color::White();
        pointLight.Intensity = 1.0f;
        pointLight.Position = Vec3f(0.0f, 0.0f, 0.0f);
        pointLight.Attenuation = Attenuation::AsSpriteLight();
        return pointLight;
    }
}
