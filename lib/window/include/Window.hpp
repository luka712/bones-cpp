#ifndef BNS_WINDOW_H

#define BNS_WINDOW_H

#include "Types.hpp"
#include "Vec2.hpp"
#include <string>

#include "BnsMetal.hpp"
#include "BnsDirectX11.hpp"
#include "BnsWebgpu.hpp"



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
        Vec2u m_windowSize;

    public:
        /**
         * @brief Get the window size.
         */
        inline Vec2u GetWindowSize() const
        {
            return m_windowSize;
        }


#ifdef __APPLE__
        /// @brief Initialize for Metal.
        virtual CA::MetalLayer *InitializeForMetal(WindowParameters windowParameters) = 0;
#endif 

#ifdef WIN32
        /// @brief Initialize for D3D11.
        virtual HWND InitializeForD3D11(WindowParameters windowParameters) = 0;
#endif
        /**
         * Gets the WGPU surface.
         */
        virtual bool InitializeForWGPU(WindowParameters windowParameters, WGPUInstance *outInstance, WGPUSurface *outSurface) = 0;
    };

} // namespace BNS
#endif