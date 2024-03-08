
#if USE_WEBGPU

#ifndef BNS_SDL2_EXTENSION_H

#define BNS_SDL2_EXTENSION_H


#include <webgpu/webgpu.h>

#include <SDL2/SDL.h>

#ifdef __cplusplus
extern "C"
{
#endif

    /// @brief Get the WGPU Surface object
    WGPUSurface GetWGPUSurface(WGPUInstance instance, SDL_Window *window);

#ifdef __cplusplus
}
#endif

#endif

#endif // 
