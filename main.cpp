

// for metal
#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#include <Metal/Metal.hpp>

// for webgpu
#define WEBGPU_CPP_IMPLEMENTATION
#include <webgpu/webgpu.hpp>

// for our use
#define USE_WEBGPU


#include <iostream>
#include <SDL2/SDL.h>

#include "Framework.hpp"


int main()
{
    bns::Framework engine;
    bns::WindowParameters parameters;
    engine.Initialize(parameters);

    return 0;
}
