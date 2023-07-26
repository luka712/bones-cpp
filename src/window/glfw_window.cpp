#include "window/glfw_window.hpp"
#include <iostream>
#include <glfw3webgpu.h>

namespace bns
{

    GLFWWindowManager::GLFWWindowManager()
    {
        m_window = nullptr;
    }

    GLFWWindowManager::~GLFWWindowManager()
    {
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }

    CA::MetalLayer *GLFWWindowManager::InitializeForMetal(WindowParameters windowParameters)
    {
        std::cout << "Not implemented!" << std::endl;

        return nullptr;
    }

    bool GLFWWindowManager::InitializeForWGPU(WindowParameters windowParameters, WGPUInstance *outInstance, WGPUSurface *outSurface) 
    {
        // assign window size
        m_windowSize.X = windowParameters.Width;
        m_windowSize.Y = windowParameters.Height;

        WGPUInstanceDescriptor desc = {};
        desc.nextInChain = nullptr;
        *outInstance = wgpuCreateInstance(&desc);
        if (!outInstance)
        {
            std::cerr << "Could not initialize WebGPU!" << std::endl;
            return false;
        }

        if (!glfwInit())
        {
            std::cerr << "Could not initialize GLFW!" << std::endl;
            return false;
        }

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        m_window = glfwCreateWindow(m_windowSize.X, m_windowSize.Y, windowParameters.Title.c_str(), NULL, NULL);
        if (m_window == nullptr)
        {
            std::cerr << "Could not open window!" << std::endl;
            return false;
        }

        std::cout << "Requesting adapter..." << std::endl;
        *outSurface = glfwGetWGPUSurface(*outInstance, m_window);

        return true;
    }
} // namespace BNS