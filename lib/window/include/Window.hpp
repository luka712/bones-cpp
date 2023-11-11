#ifndef BNS_WINDOW_H

#define BNS_WINDOW_H

#include "Types.hpp"
#include "Vec2.hpp"
#include <string>

#ifdef USE_METAL
#include "BnsMetal.hpp"
#endif // USE_METAL

#if USE_D3D11
#include "BnsDirectX11.hpp"
#endif // USE_D3D11

#ifdef USE_WEBGPU
#include "BnsWebGPU.hpp"
#endif

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
    public: 
        /// @brief Get the window size.
        virtual Vec2i GetWindowSize() = 0;

#if USE_METAL
        /// @brief Initialize for Metal.
        virtual CA::MetalLayer *InitializeForMetal(WindowParameters windowParameters) = 0;
#endif

#if USE_D3D11
        /// @brief Initialize for D3D11.
        virtual HWND InitializeForD3D11(WindowParameters windowParameters) = 0;
#endif

#if USE_WEBGPU
        /// @brief Initialize for WGPU.
        /// @param windowParameters The window parameters.
        /// @param outInstance The WGPU instance as out parameter.
        /// @param outSurface The WGPU surface as out parameter.
        /// @return True if initialization was successful, false otherwise.
        virtual bool InitializeForWGPU(WindowParameters windowParameters, WGPUInstance *outInstance, WGPUSurface *outSurface) = 0;
#endif
    };

} // namespace BNS
#endif
