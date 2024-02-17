#if USE_OPENGLES

#include "renderer/OpenGLESbns_renderer.hpp"

namespace bns
{
    OpenGLESRenderer::OpenGLESRenderer(WindowManager *window)
        : m_windowManager(window)
    {
    }

    void OpenGLESRenderer::Initialize()
    {
        m_windowManager->InitializeForOpenGLES(WindowParameters(), &m_majorVersion, &m_minorVersion);
        m_bufferSize = m_windowManager->GetWindowSize();

    }

    void OpenGLESRenderer::BeginDraw()
    {
        glViewport(0, 0, m_bufferSize.X, m_bufferSize.Y);
        glClearColor(ClearColor.R, ClearColor.G, ClearColor.B, ClearColor.A);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void OpenGLESRenderer::EndDraw()
    {
        m_windowManager->SwapBuffers();
    }

    void OpenGLESRenderer::Destroy()
    {

    }

    void *OpenGLESRenderer::GetSwapChainTexture()
    {
        return nullptr;
    }

    void OpenGLESRenderer::SetRenderTexture(Texture2D *texture)
    {
    }

    void OpenGLESRenderer::UnsetRenderTexture()
    {
    }

    void OpenGLESRenderer::SetBrightnessTexture(Texture2D *texture)
    {
    }

    void OpenGLESRenderer::UnsetBrightnessTexture()
    {
    }

    void OpenGLESRenderer::Resize()
    {
    }

}

#endif