#ifndef BNS_SDL_WINDOW_H

#define BNS_SDL_WINDOW_H

#include "Window.hpp"
#include <SDL2/SDL.h>
#include "BnsWebGPU.hpp"

namespace bns
{
    /**
     * @brief SDL implementation of WindowManager.
     */
    class SDLWindowManager final : public WindowManager
    {
    private:
        SDL_Window *m_window;
        SDL_Renderer *m_renderer;

        void CreateWindowAndRenderer(WindowParameters windowParameters);

    public:
        SDLWindowManager();
        ~SDLWindowManager();

        Vec2i GetWindowSize() override;

#if USE_WEBGPU
        bool InitializeForWGPU(WindowParameters windowParameters, WGPUInstance *outInstance, WGPUSurface *outSurface) override;
#endif

#if USE_METAL
        CA::MetalLayer *InitializeForMetal(WindowParameters windowParameters) override;
#endif // USE_METAL

#if USE_D3D11
        HWND InitializeForD3D11(WindowParameters windowParameters) override;
#endif // WIN32

#if USE_OPENGL
        void InitializeForOpenGL(WindowParameters windowParameters) override;
#endif

        void SwapBuffers() override;

        void Destroy() override;
    };
}

#endif