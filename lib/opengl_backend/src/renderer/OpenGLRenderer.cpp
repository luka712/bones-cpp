#if USE_OPENGL

#include "renderer/OpenGLbns_renderer.hpp"

namespace bns
{
    OpenGLRenderer::OpenGLRenderer(WindowManager *window)
        : m_windowManager(window)
    {
    }

    void OpenGLRenderer::Initialize()
    {
        m_windowManager->InitializeForOpenGL(WindowParameters(), &m_majorVersion, &m_minorVersion);
        m_bufferSize = m_windowManager->GetWindowSize();

    }

    void OpenGLRenderer::BeginDraw()
    {
        glViewport(0, 0, m_bufferSize.X, m_bufferSize.Y);
        glClearColor(ClearColor.R, ClearColor.G, ClearColor.B, ClearColor.A);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void OpenGLRenderer::EndDraw()
    {
        m_windowManager->SwapBuffers();
    }

    void OpenGLRenderer::Destroy()
    {

    }

    void *OpenGLRenderer::GetSwapChainTexture()
    {
        return nullptr;
    }

    void OpenGLRenderer::SetRenderTexture(Texture2D *texture)
    {
    }

    void OpenGLRenderer::UnsetRenderTexture()
    {
    }

    void OpenGLRenderer::SetBrightnessTexture(Texture2D *texture)
    {
    }

    void OpenGLRenderer::UnsetBrightnessTexture()
    {
    }

    void OpenGLRenderer::Resize()
    {
    }

}

#endif