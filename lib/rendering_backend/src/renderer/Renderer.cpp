#include "renderer/Renderer.hpp"

namespace bns
{
    Renderer::Renderer() : m_renderTexture(nullptr),
                           m_brightnessTexture(nullptr)
    {
        ClearColor = Color::LightPink();
        FrontFace = FrontFace::CounterClockwise;

        // Two frames in flight by default, for double buffering.
        m_framesInFlight = 2; 
    }

    void Renderer::SetRenderTexture(Texture2D *texture)
    {
        m_renderTexture = texture;
    }

    void Renderer::UnsetRenderTexture()
    {
        SetRenderTexture(nullptr);
    }

    void Renderer::SetBrightnessTexture(Texture2D *texture)
    {
        m_brightnessTexture = texture;
    }

    void Renderer::UnsetBrightnessTexture()
    {
        SetBrightnessTexture(nullptr);
    }
}