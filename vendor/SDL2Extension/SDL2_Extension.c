#include <Cocoa/Cocoa.h>
#include <Foundation/Foundation.h>
#include <QuartzCore/CAMetalLayer.h>

#define SDL_VIDEO_DRIVER_COCOA 1
#define __OBJC__ 1

#include "SDL2_Extension.h"
#include "SDL2/SDL_syswm.h"


WGPUSurface GetWGPUSurface(WGPUInstance instance, SDL_Window *window)
{
    SDL_SysWMinfo info;
    SDL_VERSION(&info.version);
    SDL_GetWindowWMInfo(window, &info);

#ifdef __APPLE__
    id metal_layer = NULL;
    NSWindow *ns_window = info.info.cocoa.window;
    [ns_window.contentView setWantsLayer:YES];
    metal_layer = [CAMetalLayer layer];
    [ns_window.contentView setLayer:metal_layer];
    return wgpuInstanceCreateSurface(
        instance,
        &(WGPUSurfaceDescriptor){
            .label = NULL,
            .nextInChain =
                (const WGPUChainedStruct *)&(
                    WGPUSurfaceDescriptorFromMetalLayer){
                    .chain =
                        (WGPUChainedStruct){
                            .next = NULL,
                            .sType = WGPUSType_SurfaceDescriptorFromMetalLayer,
                        },
                    .layer = metal_layer,
                },
        });
#endif
}
