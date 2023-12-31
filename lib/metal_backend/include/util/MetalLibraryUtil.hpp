#if USE_METAL

#ifndef BNS_METAL_LIBRARY_UTIL_HPP

#define BNS_METAL_LIBRARY_UTIL_HPP

#include "BnsMetal.hpp"
#include <string>

namespace bns
{
    struct MetalLibraryUtil
    {
        /**
         * @brief Create a library
         * @param device The device
         * @param shaderSource The shader source
         * @return The library
         * @note The shader source must be a string literal
         * @note Corresponds to WGPUShaderModule in WebGPU
         * 
        */
        static MTL::Library *Create(MTL::Device *device, std::string shaderSource);
    };
}

#endif

#endif // USE_METAL