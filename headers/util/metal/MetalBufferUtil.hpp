#ifndef BNS_METAL_BUFFER_UTIL_HPP

#define BNS_METAL_BUFFER_UTIL_HPP

#include <Metal/Metal.hpp>
#include <string>
#include <vector>
#include "data/Types.hpp"

namespace bns
{
    class MetalBufferUtil final
    {
    public:
        /**
         * Create a vertex buffer
         * @param device The metal device
         * @param data The data to be copied to the buffer
         * @param label The label of the buffer
         * @return The vertex buffer
         * @note The data is copied to the buffer
         */
        static MTL::Buffer *CreateVertexBuffer(MTL::Device *device,
                                               std::vector<f32> data,
                                               std::string label);
    };
}

#endif