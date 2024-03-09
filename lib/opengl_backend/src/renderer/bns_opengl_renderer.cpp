#if USE_OPENGL

#include "renderer/bns_opengl_renderer.hpp"

namespace bns
{
    OpenGLRenderer::OpenGLRenderer(WindowManager *window)
        : m_windowManager(window)
    {
    }

    void OpenGLRenderer::CreateDebugCallback()
    {
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(DebugCallback, 0);
    }

    void OpenGLRenderer::Initialize()
    {
        m_windowManager->InitializeForOpenGL(WindowParameters(), &m_majorVersion, &m_minorVersion);
        m_bufferSize = m_windowManager->GetWindowSize();

        CreateDebugCallback();
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

    void GLAPIENTRY OpenGLRenderer::DebugCallback(GLenum source,
                                                  GLenum type,
                                                  GLuint id,
                                                  GLenum severity,
                                                  GLsizei length,
                                                  const GLchar *message,
                                                  const void *userParam)
    {
        std::string typeStr = "Unknown";
        switch (type)
        {
        case GL_DEBUG_TYPE_ERROR:
            typeStr = "Error";
            break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            typeStr = "Deprecated Behavior";
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            typeStr = "Undefined Behavior";
            break;
        case GL_DEBUG_TYPE_PORTABILITY:
            typeStr = "Portability";
            break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            typeStr = "Performance";
            break;
        case GL_DEBUG_TYPE_MARKER:
            typeStr = "Marker";
            break;
        case GL_DEBUG_TYPE_PUSH_GROUP:
            typeStr = "Push Group";
            break;
        case GL_DEBUG_TYPE_POP_GROUP:
            typeStr = "Pop Group";
            break;
        case GL_DEBUG_TYPE_OTHER:
            typeStr = "Other";
            break;
        }

        std::string severityStr = "Unknown";
        switch (severity)
        {
        case GL_DEBUG_SEVERITY_HIGH:
            severityStr = "High";
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            severityStr = "Medium";
            break;
        case GL_DEBUG_SEVERITY_LOW:
            severityStr = "Low";
            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            severityStr = "Notification";
            break;
        }

        std::string msg = std::string("GL CALLBACK: ") + "type = " + typeStr + ", severity = " + severityStr + ", message = " + message + "\n";
        std::cout << msg;
    }
}

#endif