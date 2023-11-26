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

        void CreateWindowAndRenderer(WindowParameters windowParameters, Uint32 flags);

    public:
        /// @brief The constructor.
        /// @param events The framework events.
        /// @param updateCallback The update callback.
        /// @param drawCallback The draw callback.
        SDLWindowManager(Events* events, std::function<void()> updateCallback, std::function<void()> drawCallback);
        ~SDLWindowManager();

        Vec2i GetWindowSize() override;

        /// @brief If set to true, window will be closed.
        /// @note Settings this will quit the game. 
        /// @note Will be set to true on window close event, such as ALT+F4 or clicking X button.
        bool Quit;

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
        void InitializeForOpenGL(WindowParameters windowParameters, i32 majorVersion = 4, i32 minorVersion = 5) override;
#endif

#if USE_OPENGLES
        void InitializeForOpenGLES(WindowParameters windowParameters, i32 majorVersion = 3, i32 minorVersion = 2) override;
#endif

#if USE_VULKAN
        /// @brief Initializes the window for Vulkan.
        /// @param windowParameters The window parameters.
        /// @param extensions The required extensions to work with Vulkan and SDL. This will be written to and is an out parameter.
        void InitializeForVulkan(WindowParameters windowParameters, std::vector<std::string> *outExtensions) override;
        VkSurfaceKHR  CreateVulkanSurface(VkInstance instance) override;
#endif 
        void SwapBuffers() override;

        void RunEventLoop() override;

        void Destroy() override;
    };
}

#endif