#include "window/sdl_window.hpp"
#include <iostream>
#include "SDL2Extension/SDL2_Extension.h"

namespace bns
{
    SDLWindowManager::SDLWindowManager()
    {
        m_window = nullptr;
        m_renderer = nullptr;
    }

    SDLWindowManager::~SDLWindowManager()
    {
        if (m_renderer != nullptr)
            SDL_DestroyRenderer(m_renderer);
        if (m_window != nullptr)
            SDL_DestroyWindow(m_window);
        SDL_Quit();
    }

    void SDLWindowManager::CreateWindowAndRenderer(WindowParameters windowParameters)
    {
        // Last parameters is for SDL flags, such as window size etc...
        int x_pos = windowParameters.PosX;
        int y_pos = windowParameters.PosY;
        if (windowParameters.Centered)
        {
            x_pos = SDL_WINDOWPOS_CENTERED;
            y_pos = SDL_WINDOWPOS_CENTERED;
        }

        Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI;
        if (windowParameters.FullScreen)
        {
            flags |= SDL_WINDOW_FULLSCREEN;
        }
        if (windowParameters.Resizable)
        {
            flags |= SDL_WINDOW_RESIZABLE;
        }

        // Set metal hint
        SDL_SetHint(SDL_HINT_RENDER_DRIVER, "metal");

        // create window
        m_window = SDL_CreateWindow(windowParameters.Title.c_str(), x_pos, y_pos, windowParameters.Width, windowParameters.Height, flags);
        if (m_window == nullptr)
        {
            SDL_Log("Failed to create SDL window: %s", SDL_GetError());
            SDL_Quit();
            throw std::runtime_error("Failed to create SDL window");
        }

        // create renderer
        m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (m_renderer == nullptr)
        {
            SDL_Log("Failed to create SDL renderer: %s", SDL_GetError());
            SDL_Quit();
            throw std::runtime_error("Failed to create SDL renderer");
        }

        // query the window size
        int width;
        int height;
        SDL_GetWindowSize(m_window, &width, &height);
        m_windowSize = Vec2u(width, height);
    }

#ifdef __APPLE__
    CA::MetalLayer *SDLWindowManager::InitializeForMetal(WindowParameters windowParameters)
    {
        CreateWindowAndRenderer(windowParameters);
        return (CA::MetalLayer *)SDL_RenderGetMetalLayer(m_renderer);
    }
#endif // __APPLE__

    bool SDLWindowManager::InitializeForWGPU(WindowParameters windowParameters, WGPUInstance *outInstance, WGPUSurface *outSurface)
    {
        CreateWindowAndRenderer(windowParameters);

        WGPUInstanceDescriptor desc = {};
        desc.nextInChain = nullptr;
        *outInstance = wgpuCreateInstance(&desc);
        if (!outInstance)
        {
            std::cerr << "Could not initialize WebGPU!" << std::endl;
            return false;
        }
        *outSurface = GetWGPUSurface(*outInstance, m_window);
        
        return true;
    }
} // namespace BNS