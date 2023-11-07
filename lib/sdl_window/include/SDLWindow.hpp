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
#ifdef USE_WEBGPU
        bool InitializeForWGPU(WindowParameters windowParameters, WGPUInstance *outInstance, WGPUSurface *outSurface) override;
#endif 

#ifdef __APPLE__
        CA::MetalLayer *InitializeForMetal(WindowParameters windowParameters) override;
#endif // __APPLE__

#ifdef WIN32
        HWND InitializeForD3D11(WindowParameters windowParameters) override;
#endif // WIN32
    };
}

#endif