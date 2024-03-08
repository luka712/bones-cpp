#if USE_METAL

#ifndef BNS_METAL_LIBRARY_UTIL_HPP

#define BNS_METAL_LIBRARY_UTIL_HPP

#include "bns_metal.hpp"
#include <string>

namespace bns
{
    /// @brief The Metal library utility class. 
    struct MetalLibraryUtil
    {

        /// @brief Create a Metal library.
        /// @param device The device.
        /// @param shaderSource The shader source.
        /// @param label The label.
        /// @return The library.
        static MTL::Library *Create(MTL::Device *device, std::string shaderSource, std::string label = "");
    };
}

#endif

#endif // USE_METAL