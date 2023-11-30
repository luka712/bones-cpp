#if USE_OPENGL

#ifndef BNS_OPENGL_RENDERER_HPP

#define BNS_OPENGL_RENDERER_HPP

#include "BnsOpenGL.hpp"
#include "renderer/Renderer.hpp"
#include "Window.hpp"

namespace bns
{
    class OpenGLRenderer final : public Renderer
    {
    private:
        WindowManager *m_windowManager;

        /// @brief The major version of OpenGL.
        i32 m_majorVersion;

        /// @brief The minor version of OpenGL.
        i32 m_minorVersion;

        /// @brief Resizes the swap chain.
        void Resize();

    public:
        OpenGLRenderer(WindowManager *window);

        /// @brief Gets the renderer type.
        /// @return The renderer type.
        RendererType GetRendererType() const override { return RendererType::OpenGL; }

        /// @brief Gets the major version of OpenGL.
        inline i32 GetMajorVersion() const { return m_majorVersion; }

        /// @brief Gets the minor version of OpenGL.
        inline i32 GetMinorVersion() const { return m_minorVersion; }

        /// @brief Falls back to OpenGL 4.0.
        /// @return True if the renderer falls back to OpenGL 4.
        inline bool FallbackTo400Version() const { return m_majorVersion == 4 && m_minorVersion < 5; }

        void *GetSwapChainTexture() override;

        void SetRenderTexture(Texture2D *texture) override;

        void UnsetRenderTexture() override;

        void SetBrightnessTexture(Texture2D *texture) override;

        void UnsetBrightnessTexture() override;

        /// @brief Initializes the renderer.
        void Initialize();
        void BeginDraw() override;
        void EndDraw() override;
        void Destroy() override;
    };
}

#endif // BNS_OPENGL_RENDERER_HPP

#endif // USE_OPENGL