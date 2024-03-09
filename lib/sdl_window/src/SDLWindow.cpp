#include "SDLWindow.hpp"
#include <iostream>

#if USE_WEBGPU
#include "SDL2Extension/SDL2_Extension.h"
#endif 

// To get correct struct from <SDL2\SDL_syswm.h>, we must define.
#if WIN32
#define SDL_VIDEO_DRIVER_WINDOWS 1
#include <SDL2\SDL_syswm.h>
#endif // WIN32

#include <exception>

#if USE_VULKAN
#include <SDL2/SDL_vulkan.h>
#endif

#define GL_ES_VERSION_3_0 1

namespace bns
{
    SDLWindowManager::SDLWindowManager(Events *events, TimeManager *timeManager, std::function<void(Time time)> updateCallback, std::function<void()> drawCallback)
        : WindowManager(events, timeManager, updateCallback, drawCallback), m_timeManager(timeManager), Quit(false)
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

    void SDLWindowManager::CreateSDLWindow(WindowParameters windowParameters, Uint32 flags)
    {
        // Destroy window and renderer if they exist
        if (m_renderer != nullptr)
            SDL_DestroyRenderer(m_renderer);
        if (m_window != nullptr)
            SDL_DestroyWindow(m_window);

        // Last parameters is for SDL flags, such as window size etc...
        int x_pos = windowParameters.PosX;
        int y_pos = windowParameters.PosY;
        if (windowParameters.Centered)
        {
            x_pos = SDL_WINDOWPOS_CENTERED;
            y_pos = SDL_WINDOWPOS_CENTERED;
        }

        flags |= SDL_WINDOW_ALLOW_HIGHDPI;
        if (windowParameters.FullScreen)
        {
            flags |= SDL_WINDOW_FULLSCREEN;
        }
        if (windowParameters.Resizable)
        {
            flags |= SDL_WINDOW_RESIZABLE;
        }

        // create window
        m_window = SDL_CreateWindow(windowParameters.Title.c_str(), x_pos, y_pos, windowParameters.Width, windowParameters.Height, flags);
        if (m_window == nullptr)
        {
            std::string msg = "SDLWindowManager::CreateWindowAndRenderer: Failed to create SDL window: " + std::string(SDL_GetError());
            LOG(msg);
            SDL_Quit();
            throw std::runtime_error(msg);
        }
        LOG("SDLWindowManager::CreateWindowAndRenderer: Created SDL window: " + windowParameters.Title);
    }

    void SDLWindowManager::CreateSDLWindowAndRenderer(WindowParameters windowParameters, Uint32 flags)
    {
        CreateSDLWindow(windowParameters, flags);

        // create renderer
        m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        if (m_renderer == nullptr)
        {
            std::string msg = "SDLWindowManager::CreateWindowAndRenderer: Failed to create SDL renderer: " + std::string(SDL_GetError());
            LOG(msg);
            SDL_Quit();
            throw std::runtime_error(msg.c_str());
        }
        LOG("SDLWindowManager::CreateWindowAndRenderer: Created SDL renderer: " + windowParameters.Title);
    }

#if USE_WEBGPU
    bool SDLWindowManager::InitializeForWGPU(WindowParameters windowParameters, WGPUInstance *outInstance, WGPUSurface *outSurface)
    {
        CreateSDLWindowAndRenderer(windowParameters, 0);

        WGPUInstanceDescriptor desc = {};
        desc.nextInChain = nullptr;
        *outInstance = wgpuCreateInstance(&desc);
        if (!outInstance)
        {
            std::string msg = "SDLWindowManager::InitializeForWGPU: Failed to create WGPU instance";
            LOG(msg);
            throw std::runtime_error(msg.c_str());
        }
        *outSurface = GetWGPUSurface(*outInstance, m_window);

        return true;
    }
#endif

#if USE_METAL
    CA::MetalLayer *SDLWindowManager::InitializeForMetal(WindowParameters windowParameters)
    {
        CreateSDLWindowAndRenderer(windowParameters, SDL_WINDOW_METAL);

        CA::MetalLayer *metalLayer = (CA::MetalLayer *)SDL_RenderGetMetalLayer(m_renderer);

        if (metalLayer == nullptr)
        {
            std::string msg = "SDLWindowManager::InitializeForMetal: Failed to create SDL renderer: " + std::string(SDL_GetError());
            LOG(msg);
            BREAKPOINT();
            throw std::runtime_error(msg.c_str());
        }

        NS::String *nsDeviceName = metalLayer->device()->name();
        std::string deviceName = std::string(nsDeviceName->cString(NS::StringEncoding::ASCIIStringEncoding));
        LOG("SDLWindowManager::InitializeForMetal: Metal Enabled. Metal Device: " << deviceName << ".");

        return metalLayer;
    }
#endif // __APPLE__

#if USE_D3D11
    HWND SDLWindowManager::InitializeForD3D11(WindowParameters windowParameters)
    {
        CreateSDLWindowAndRenderer(windowParameters, 0);

        SDL_SysWMinfo systemInfo;
        SDL_VERSION(&systemInfo.version);
        SDL_GetWindowWMInfo(m_window, &systemInfo);

        HWND handle = systemInfo.info.win.window;
        return handle;
    }
#endif // USE_D3D11

#if USE_OPENGL
    void SDLWindowManager::InitializeForOpenGL(WindowParameters windowParameters, i32 *outMajorVersion, i32 *outMinorVersion)
    {
        CreateSDLWindow(windowParameters, SDL_WINDOW_OPENGL);

        // engine automatically tries the highest version of OpenGL, but it not guaranteed to work.
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); // OpenGL core profile
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);                          // we want OpenGL 4.6
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);

        SDL_GLContext glContext = SDL_GL_CreateContext(m_window);

        if (glContext == nullptr)
        {
            std::string msg = "SDLWindowManager::InitializeForOpenGL: Failed to create SDL renderer: " + std::string(SDL_GetError());
            LOG(msg);
            BREAKPOINT();
            throw std::runtime_error(msg.c_str());
        }

        // Initialize Glad (after creating an OpenGL context)
        if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
        {
            std::string msg = "SDLWindowManager::InitializeForOpenGL: Failed to create SDL renderer: " + std::string(SDL_GetError());
            LOG(msg);
            BREAKPOINT();
            throw std::runtime_error(msg.c_str());
        }

        // GLAD is now loaded, we can use OpenGL functions. Get the version of OpenGL we are using.
        *outMajorVersion = GLVersion.major;
        *outMinorVersion = GLVersion.minor;

        std::string log = "SDLWindowManager::InitializeForOpenGL: OpenGL Version: " + std::string((const char *)glGetString(GL_VERSION));
        LOG(log);
    }
#endif // USE_OPENGL

#if USE_OPENGLES
    void SDLWindowManager::InitializeForOpenGLES(WindowParameters windowParameters, i32 *outMajorVersion, i32 *outMinorVersion)
    {
        CreateSDLWindow(windowParameters, SDL_WINDOW_OPENGL);

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); // OpenGLES profile
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);                          // we want OpenGLES 3.2
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

        SDL_GLContext glContext = SDL_GL_CreateContext(m_window);

        if (glContext == nullptr)
        {
            std::string msg = "SDLWindowManager::InitializeForOpenGLES: Failed to create SDL renderer: " + std::string(SDL_GetError());
            LOG(msg);
            BREAKPOINT();
            throw std::runtime_error(msg.c_str());
        }

        // Initialize Glad (after creating an OpenGL context)
        if (!gladLoadGLES2Loader((GLADloadproc)SDL_GL_GetProcAddress))
        {
            std::string msg = "SDLWindowManager::InitializeForOpenGLES: Failed to create SDL renderer: " + std::string(SDL_GetError());
            LOG(msg);
            BREAKPOINT();
            throw std::runtime_error(msg.c_str());
        }

        // GLAD is now loaded, we can use OpenGL functions. Get the version of OpenGLES we are using.
        *outMajorVersion = GLVersion.major;
        *outMinorVersion = GLVersion.minor;

        LOG("SDLWindowManager::InitializeForOpenGLES: OpenGLES Version: %s", glGetString(GL_VERSION));
    }
#endif // USE_OPENGLES

#if USE_VULKAN

    void SDLWindowManager::InitializeForVulkan(WindowParameters windowParameters, std::vector<std::string> *outRequiredExtensions)
    {
        CreateSDLWindowAndRenderer(windowParameters, SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE);

        // Get the extensions count. We need the count to allocate the array of extensions.
        u32 extensionCount = 0;
        if (!SDL_Vulkan_GetInstanceExtensions(m_window, &extensionCount, nullptr))
        {
            std::string msg = "SDLWindowManager::InitializeForVulkan: Failed to get Vulkan extensions count: " + std::string(SDL_GetError()) + "\n";
            LOG(msg);
            BREAKPOINT();
            throw std::runtime_error(msg.c_str());
        }

        // allocate the array of extensions
        std::vector<const char *> pExtensions(extensionCount);

        LOG("SDLWindowManager::InitializeForVulkan: Vulkan Extensions Count: " + extensionCount);

        // Get the extensions
        if (!SDL_Vulkan_GetInstanceExtensions(m_window, &extensionCount, pExtensions.data()))
        {
            std::string msg = "SDLWindowManager::InitializeForVulkan: Failed to get Vulkan extensions: " + std::string(SDL_GetError()) + "\n";
            LOG(msg);
            BREAKPOINT();
            throw std::runtime_error(msg.c_str());
        }

        for (u32 i = 0; i < extensionCount; ++i)
        {
            LOG("SDLWindowManager::InitializeForVulkan: Available Vulkan Extension: " + std::string(pExtensions[i]));

            outRequiredExtensions->push_back(pExtensions[i]);
        }
    };

    VkSurfaceKHR SDLWindowManager::CreateVulkanSurface(VkInstance instance)
    {
        VkSurfaceKHR surface;
        if (!SDL_Vulkan_CreateSurface(m_window, instance, &surface))
        {
            std::string msg = "SDLWindowManager::CreateVulkanSurface: Failed to create Vulkan surface: " + std::string(SDL_GetError()) + "\n";
            LOG(msg);
            BREAKPOINT();
            throw std::runtime_error(msg.c_str());
        }

        LOG("SDLWindowManager::CreateVulkanSurface: Created Vulkan surface.\n");

        surface = surface;

        return surface;
    }

#endif

    void SDLWindowManager::RunEventLoop()
    {
        m_timeManager->PrepareStart();
        m_events->ClearEvents();
        SDL_Event event;

        while (!Quit)
        {
            // Start frame
            m_timeManager->Start();

            // Process events
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    m_events->AddEvent(EventType::WindowClose);
                    Quit = true;
                }
                else if (event.type == SDL_WINDOWEVENT)
                {
                    switch (event.window.event)
                    {
                    case SDL_WINDOWEVENT_RESIZED:
                    {
                        // Create event
                        EventData data;
                        data.Vec2i[0] = event.window.data1;
                        data.Vec2i[1] = event.window.data2;
                        m_events->AddEvent(EventType::WindowResize, data);

                        // We also have callback, call here.
                        for (auto &callback : m_windowResizeEventCallbacks)
                        {
                            callback(Vec2i(event.window.data1, event.window.data2));
                        }
                        break;
                    }
                    case SDL_WINDOWEVENT_CLOSE:
                    {
                        m_events->AddEvent(EventType::WindowClose);
                        Quit = true;
                        break;
                    }
                    default:
                        break;
                    }
                }
                else if (event.type == SDL_KEYDOWN)
                {
                    EventData data;
                    data.I32 = event.key.keysym.sym;
                    m_events->AddEvent(EventType::KeyDown, data);
                }
            }

            m_updateCallback(m_timeManager->GetTime());
            m_drawCallback();

            // End frame
            m_timeManager->End();

            LOG("FPS: " << m_timeManager->GetFPS());
        }
    }

    void SDLWindowManager::SwapBuffers()
    {
#if USE_OPENGL | USE_OPENGLES
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
