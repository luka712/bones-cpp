#if USE_WEBGPU

#include "util/bns_webgpu_converter.hpp"

namespace bns
{
    WGPUTextureFormat WebGPUConverter::Convert(TextureFormat format)
    {
        switch (format)
        {
        case TextureFormat::RGBA_8_Unorm:
            return WGPUTextureFormat_RGBA8Unorm;
        case TextureFormat::BGRA_8_Unorm:
            return WGPUTextureFormat_BGRA8Unorm;
        default:
            throw std::runtime_error("Unknown texture format");
        }
    }
}

#endif 