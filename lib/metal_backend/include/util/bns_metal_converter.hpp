#if USE_METAL

#ifndef BNS_METAL_CONVERTER

#define BNS_METAL_CONVERTER

#include "bns_metal.hpp"
#include "bns_rendering_backend_types.hpp"

namespace bns
{
    /// @brief Converts Bones formats to Metal formats.
    struct MetalConverter
    {
        /// @brief Convert the texture format to Metal texture format.
        /// @param format The texture format.
        /// @return The Metal texture format.
        static MTL::PixelFormat Convert(TextureFormat format);

        /// @brief Convert the texture usage flags to Metal texture usage flags.
        /// @param textureUsageFlags The texture usage flags.
        /// @return The Metal texture usage flags.
        static MTL::TextureUsage Convert(TextureUsage textureUsageFlags);
    };
}

#endif

#endif // USE_METAL