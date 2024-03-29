#include "renderer/bns_renderer.hpp"

namespace bns
{
    Renderer::Renderer(SurfacePresentationMode presentationMode) : m_renderTexture(nullptr),
                           m_brightnessTexture(nullptr)
    {
        ClearColor = Color::LightPink();
        FrontFace = FrontFace::CounterClockwise;

        // Two frames in flight by default, for double buffering.
        m_framesInFlight = 2; 
        m_presentationMode = presentationMode;
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