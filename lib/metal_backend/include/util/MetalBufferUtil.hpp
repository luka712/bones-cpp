#if USE_METAL

#ifndef BNS_METAL_BUFFER_UTIL_HPP

#define BNS_METAL_BUFFER_UTIL_HPP

#include "BnsMetal.hpp"
#include <string>
#include <vector>
#include "Types.hpp"

namespace bns
{
    class MetalBufferUtil final
    {
    public:
        /**
         * Create a buffer with u32 data.
         */
        template <typename T>
        static MTL::Buffer *Create(MTL::Device *device,
                                         std::vector<T> data,
                                         std::string label)
        {
            size_t byteSize = data.size() * sizeof(T);

            MTL::Buffer *buffer = device->newBuffer(data.data(), byteSize, MTL::ResourceOptionCPUCacheModeDefault);
            NS::String *nsLabel = NS::String::string(label.c_str(), NS::StringEncoding::UTF8StringEncoding);
            buffer->setLabel(nsLabel);
            nsLabel->release();

            return buffer;
        }

        /**
         * Create a buffer with u32 data.
         */
        template <typename T>
        static MTL::Buffer *Create(MTL::Device *device,
                                         size_t byteSize,
                                         std::string label)
        {
            MTL::Buffer *buffer = device->newBuffer(byteSize, MTL::ResourceOptionCPUCacheModeDefault);
            NS::String *nsLabel = NS::String::string(label.c_str(), NS::StringEncoding::UTF8StringEncoding);
            buffer->setLabel(nsLabel);
            nsLabel->release();

            return buffer;
        }
    };
}

#endif

#endif // __APPLE__