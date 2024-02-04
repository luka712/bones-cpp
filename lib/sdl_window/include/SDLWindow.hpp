#ifndef BNS_SDL_WINDOW_H

#define BNS_SDL_WINDOW_H

#include "Window.hpp"
#include <SDL2/SDL.h>
#include "time/TimeManager.hpp"

namespace bns
{
        /// @brief SDL implementation of WindowManager.
        class SDLWindowManager final : public WindowManager
        {
        private:
                TimeManager *m_timeManager;

                SDL_Window *m_window;
                SDL_Renderer *m_renderer;

                f32 m_currentFrameTime;
                f32 m_lastFrameTime;

                /// @brief Creates a window. Sometimes renderer is not needed (OpenGL, Vulkan, etc.)
                /// @param windowParameters The window parameters.
                /// @param flags The flags.
                /// @note Named CreateSDLWindow to avoid confusion with CreateWindow from WinUser.h of Windows.
                void CreateSDLWindow(WindowParameters windowParameters, Uint32 flags);

                /// @brief Creates a window and renderer.
                /// @param windowParameters The window parameters.
                /// @param flags The flags.
                /// @note Named CreateSDLWindowAndRenderer to to keep it consistent with @ref CreateSDLWindow.
                void CreateSDLWindowAndRenderer(WindowParameters windowParameters, Uint32 flags);

        public:
                /// @brief The constructor.
                /// @param events The framework events.
                /// @param timeManager The time manager.
                /// @param updateCallback The update callback.
                /// @param drawCallback The draw callback.
                SDLWindowManager(Events *events, TimeManager *timeManager, std::function<void(Time)> updateCallback, std::function<void()> drawCallback);
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
                void InitializeForOpenGL(WindowParameters windowParameters, i32 *outMajorVersion, i32 *outMinorVersion) override;
#endif

#if USE_OPENGLES
                void InitializeForOpenGLES(WindowParameters windowParameters, i32 *outMajorVersion, i32 *outMinorVersion) override;
#endif

#if USE_VULKAN
                /// @brief Initializes the window for Vulkan.
                /// @param windowParameters The window parameters.
                /// @param extensions The required extensions to work with Vulkan and SDL. This will be written to and is an out parameter.
                void InitializeForVulkan(WindowParameters windowParameters, std::vector<std::string> *outExtensions) override;
                VkSurfaceKHR CreateVulkanSurface(VkInstance instance) override;
#endif
                void SwapBuffers() override;

                void RunEventLoop() override;

                void Destroy() override;
        };
}

#endif