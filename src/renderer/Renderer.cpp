#include "renderer/Renderer.hpp"
#include "Framework.hpp"

namespace bns
{
    Renderer::Renderer(Framework &framework) : m_framework(framework), m_renderTexture(nullptr)
    {
        ClearColor = Color::LightPink();
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