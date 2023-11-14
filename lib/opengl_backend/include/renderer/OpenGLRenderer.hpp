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

        /// @brief Resizes the swap chain.
        void Resize();

    public:
        OpenGLRenderer(WindowManager *window);

        void *GetSwapChainTexture() override;

        void SetRenderTexture(Texture2D *texture) override;

        void UnsetRenderTexture() override;

        void SetBrightnessTexture(Texture2D *texture) override;

        void UnsetBrightnessTexture() override;

        void Initialize();
        void BeginDraw() override;
        void EndDraw() override;
        void Destroy() override;
    };
}

#endif // BNS_OPENGL_RENDERER_HPP

#endif // USE_OPENGL