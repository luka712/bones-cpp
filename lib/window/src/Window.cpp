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

}
