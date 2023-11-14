#include "SDLWindow.hpp"
#include <iostream>
#include "SDL2Extension/SDL2_Extension.h"

// To get correct struct from <SDL2\SDL_syswm.h>, we must define.
#if WIN32
#define SDL_VIDEO_DRIVER_WINDOWS 1
#include <SDL2\SDL_syswm.h>
#endif // WIN32

#include <exception>

namespace bns
{
    SDLWindowManager::SDLWindowManager()
        : WindowManager()
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

    Vec2i SDLWindowManager::GetWindowSize()
    {
        int width, height;
        SDL_GetWindowSize(m_window, &width, &height);
        return Vec2i(width, height);
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
            std::string msg = "SDLWindowManager::CreateWindowAndRenderer: Failed to create SDL window: " + std::string(SDL_GetError());
            SDL_Log(msg.c_str());
            SDL_Quit();
            throw std::exception(msg.c_str());
        }

        // create renderer
        m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (m_renderer == nullptr)
        {
            std::string msg = "SDLWindowManager::CreateWindowAndRenderer: Failed to create SDL renderer: " + std::string(SDL_GetError());
            SDL_Log(msg.c_str());
            SDL_Quit();
            throw std::exception(msg.c_str());
        }
    }

#if USE_WEBGPU
    bool SDLWindowManager::InitializeForWGPU(WindowParameters windowParameters, WGPUInstance *outInstance, WGPUSurface *outSurface)
    {
        CreateWindowAndRenderer(windowParameters);

        WGPUInstanceDescriptor desc = {};
        desc.nextInChain = nullptr;
        *outInstance = wgpuCreateInstance(&desc);
        if (!outInstance)
        {
            std::string msg = "SDLWindowManager::InitializeForWGPU: Failed to create WGPU instance";
            SDL_Log(msg.c_str());
            throw std::exception(msg.c_str());
        }
        *outSurface = GetWGPUSurface(*outInstance, m_window);

        return true;
    }
#endif

#if USE_METAL
    CA::MetalLayer *SDLWindowManager::InitializeForMetal(WindowParameters windowParameters)
    {
        CreateWindowAndRenderer(windowParameters);
        return (CA::MetalLayer *)SDL_RenderGetMetalLayer(m_renderer);
    }
#endif // __APPLE__

#if USE_D3D11
    HWND SDLWindowManager::InitializeForD3D11(WindowParameters windowParameters)
    {
        CreateWindowAndRenderer(windowParameters);

        SDL_SysWMinfo systemInfo;
        SDL_VERSION(&systemInfo.version);
        SDL_GetWindowWMInfo(m_window, &systemInfo);

        HWND handle = systemInfo.info.win.window;
        return handle;
    }
#endif // USE_D3D11

#if USE_OPENGL
    void SDLWindowManager::InitializeForOpenGL(WindowParameters windowParameters)
    {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); // OpenGL core profile
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);                          // OpenGL 4+
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);                          // OpenGL 4.5

        CreateWindowAndRenderer(windowParameters);
        SDL_GLContext glContext = SDL_GL_CreateContext(m_window);

        // Initialize Glad (after creating an OpenGL context)
        if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
        {
            std::string msg = "SDLWindowManager::InitializeForOpenGL: Failed to create SDL renderer: " + std::string(SDL_GetError());
            SDL_Log(msg.c_str());
            throw std::exception(msg.c_str());
        }
    }
#endif // USE_OPENGL

    void SDLWindowManager::SwapBuffers()
    {
#if USE_OPENGL
        SDL_GL_SwapWindow(m_window);
#endif
    }

    void SDLWindowManager::Destroy()
    {
        if (m_renderer != nullptr)
            SDL_DestroyRenderer(m_renderer);
        if (m_window != nullptr)
            SDL_DestroyWindow(m_window);
        SDL_Quit();
    }

} // namespace BNS