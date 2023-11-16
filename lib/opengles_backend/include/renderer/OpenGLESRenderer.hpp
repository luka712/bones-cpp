#if USE_OPENGLES

#ifndef BNS_OPENGLES_RENDERER_HPP

#define BNS_OPENGLES_RENDERER_HPP

#include "BnsOpenGLES.hpp"
#include "renderer/Renderer.hpp"
#include "Window.hpp"

namespace bns
{
    class OpenGLESRenderer final : public Renderer
    {
    private:
        WindowManager *m_windowManager;

        /// @brief Resizes the swap chain.
        void Resize();

    public:
        OpenGLESRenderer(WindowManager *window);

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

#endif // BNS_OPENGLES_RENDERER_HPP

#endif // USE_OPENGLES