#include "window/sdl_window.hpp"
#include <iostream>

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

    CA::MetalLayer *SDLWindowManager::InitializeForMetal(WindowParameters windowParameters)
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
            return nullptr;
        }

        // create renderer
        m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (m_renderer == nullptr)
        {
            SDL_Log("Failed to create SDL renderer: %s", SDL_GetError());
            SDL_Quit();
            return nullptr;
        }

        // query the window size
        SDL_GetWindowSize(m_window, &m_windowSize.X, &m_windowSize.Y);

        return (CA::MetalLayer *)SDL_RenderGetMetalLayer(m_renderer);
    }

    bool SDLWindowManager::InitializeForWGPU(WindowParameters windowParameters, WGPUInstance *outInstance, WGPUSurface *outSurface) 
    {
        std::cout << "InitializeForWGPU not implemented for SDL" << std::endl;
        return false;
    }
} // namespace BNS