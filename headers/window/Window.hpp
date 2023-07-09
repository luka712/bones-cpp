#ifndef BNS_WINDOW_H

#define BNS_WINDOW_H

#include "data/Types.hpp"
#include "data/Vec2.hpp"
#include <string>

#include "Metal/Metal.hpp"

#include <webgpu/webgpu.h>

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
        Vec2i m_windowSize;

    public:
        /**
         * @brief Get the window size.
         */
        inline Vec2i GetWindowSize() const
        {
            return m_windowSize;
        }

        /**
         * @brief Initialize for Metal.
         */
        virtual CA::MetalLayer *InitializeForMetal(WindowParameters windowParameters) = 0;

        /**
         * Gets the WGPU surface.
         */
        virtual bool InitializeForWGPU(WindowParameters windowParameters, WGPUInstance *outInstance, WGPUSurface *outSurface) = 0;
    };

} // namespace BNS
#endif