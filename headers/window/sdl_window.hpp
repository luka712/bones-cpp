#ifndef BNS_SDL_WINDOW_H

#define BNS_SDL_WINDOW_H

#include "window/Window.hpp"
#include <SDL2/SDL.h>

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
        bool InitializeForWGPU(WindowParameters windowParameters, WGPUInstance *outInstance, WGPUSurface *outSurface) override;
#ifdef __APPLE__
        CA::MetalLayer *InitializeForMetal(WindowParameters windowParameters) override;
#endif // __APPLE__
    };
}

#endif