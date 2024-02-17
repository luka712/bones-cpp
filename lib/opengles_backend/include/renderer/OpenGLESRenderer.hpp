#if USE_OPENGLES

#ifndef BNS_OPENGLES_RENDERER_HPP

#define BNS_OPENGLES_RENDERER_HPP

#include "BnsOpenGLES.hpp"
#include "renderer/bns_renderer.hpp"
#include "Window.hpp"

namespace bns
{
    class OpenGLESRenderer final : public Renderer
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
        OpenGLESRenderer(WindowManager *window);

        /// @brief Gets the renderer type.
        /// @return The renderer type.
        RendererType GetRendererType() const override { return RendererType::OpenGLES; }

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

#endif // BNS_OPENGLES_RENDERER_HPP

#endif // USE_OPENGLES