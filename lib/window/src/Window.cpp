#include "Window.hpp"

namespace bns
{
    WindowParameters::WindowParameters()
    {
        Title = "BNS";
        PosX = -1;
        PosY = -1;
        Width = 800;
        Height = 600;
        Centered = true;
        FullScreen = false;
        Resizable = false;
    }

    WindowManager::WindowManager(Events *events, std::function<void()> updateCallback, std::function<void()> drawCallback)
        : m_events(events), m_updateCallback(updateCallback), m_drawCallback(drawCallback)
    {
    }

    void WindowManager::RegisterToWindowResize(std::function<void(Vec2i size)> callback)
    {
        m_windowResizeEventCallbacks.push_back(callback);
    }
}
