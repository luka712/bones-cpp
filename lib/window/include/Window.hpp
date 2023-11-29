#ifndef BNS_WINDOW_H

#define BNS_WINDOW_H

#include "Types.hpp"
#include "Vec2.hpp"
#include <string>
#include "Event.hpp"
#include <functional>

#if USE_METAL
#include "BnsMetal.hpp"
#endif // USE_METAL

#if USE_D3D11
#include "BnsDirectX11.hpp"
#endif // USE_D3D11

#if USE_WEBGPU
#include "BnsWebGPU.hpp"
#endif

#if USE_OPENGL
#include "BnsOpenGL.hpp"
#endif // USE_OPENGL

#if USE_OPENGLES
#include "BnsOpenGLES.hpp"
#endif // USE_OPENGLES

#if USE_VULKAN
#include "BnsVulkan.hpp"
#endif // USE_VULKAN

namespace bns
{
        struct WindowParameters
        {
                WindowParameters();

                std::string Title;
                i32 PosX;
                i32 PosY;
                i32 Width;
                i32 Height;
                bool Centered;

                /**
                 * @brief If set full screen is used.
                 */
                bool FullScreen;

                /**
                 * @brief Is set, created window should be resizable.
                 */
                bool Resizable;
        };

        class WindowManager
        {
        protected:
                Events *m_events;

                /// @brief The update callback.
                std::function<void()> m_updateCallback;

                /// @brief The draw callback.
                std::function<void()> m_drawCallback;

        public:
                /// @brief The constructor.
                /// @param events The events.
                /// @param updateCallback The update callback.
                /// @param drawCallback The draw callback.
                WindowManager(Events *events, std::function<void()> updateCallback, std::function<void()> drawCallback);

                /// @brief Get the window size.
                virtual Vec2i GetWindowSize() = 0;

                /// @brief Creates a window.
                /// @param windowParameters The window parameters.
                virtual void CreateWindow(WindowParameters windowParameters) = 0;

#if USE_METAL
                /// @brief Initialize for Metal.
                virtual CA::MetalLayer *InitializeForMetal(WindowParameters windowParameters) = 0;
#endif

#if USE_D3D11
                /// @brief Initialize for D3D11.
                virtual HWND InitializeForD3D11(WindowParameters windowParameters) = 0;
#endif

#if USE_OPENGL
                /// @brief Initialize for OpenGL.
                /// @param windowParameters The window parameters.
                virtual void InitializeForOpenGL(WindowParameters windowParameters, i32 majorVersion = 4, i32 minorVersion = 5) = 0;
#endif

#if USE_OPENGLES
                /// @brief Initialize for OpenGLES.
                /// @param windowParameters The window parameters.
                virtual void InitializeForOpenGLES(WindowParameters windowParameters, i32 majorVersion = 3, i32 minorVersion = 2) = 0;
#endif

#if USE_WEBGPU
                /// @brief Initialize for WGPU.
                /// @param windowParameters The window parameters.
                /// @param outInstance The WGPU instance as out parameter.
                /// @param outSurface The WGPU surface as out parameter.
                /// @return True if initialization was successful, false otherwise.
                virtual bool InitializeForWGPU(WindowParameters windowParameters, WGPUInstance *outInstance, WGPUSurface *outSurface) = 0;
#endif

#if USE_VULKAN
                /// @brief Initialize for Vulkan.
                /// @param windowParameters The window parameters.
                /// @param outExtensions The Vulkan extensions which are required to work with Vulkan and Window. This is out result.
                virtual void InitializeForVulkan(WindowParameters windowParameters, std::vector<std::string> *outExtensions) = 0;

                /// @brief Creates the vulkan surface.
                /// @param instance The vulkan instance.
                /// @return The vulkan surface.
                virtual VkSurfaceKHR CreateVulkanSurface(VkInstance instance) = 0;
#endif

                /// @brief Starts the window event loop and calls the update and draw callbacks.
                virtual void RunEventLoop() = 0;

                /// @brief Swap buffers.
                virtual void SwapBuffers() = 0;

                /// @brief Destroy the window.
                virtual void Destroy() = 0;
        };

} // namespace BNS
#endif
