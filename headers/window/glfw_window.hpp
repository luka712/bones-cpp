#ifndef BNS_GLFW_WINDOW_H

#define BNS_GLFW_WINDOW_H

#include "window/Window.hpp"
#include <GLFW/glfw3.h>

namespace bns
{
    /**
     * @brief SDL implementation of WindowManager.
     */
    class GLFWWindowManager : public WindowManager
    {
    private:




    public:

// TODO: should be private
        GLFWwindow *m_window;

        GLFWWindowManager();
        ~GLFWWindowManager();
        CA::MetalLayer *InitializeForMetal(WindowParameters windowParameters) override;
        bool InitializeForWGPU(WindowParameters windowParameters, WGPUInstance* outInstance, WGPUSurface* outSurface) override;
    };
}

#endif