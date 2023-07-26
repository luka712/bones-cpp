#ifndef BNS_WEBGPU_BUFFER_UTIL_HPP

#define BNS_WEBGPU_BUFFER_UTIL_HPP

#include <webgpu/webgpu.h>
#include <vector>
#include <string>
#include "data/Types.hpp"

namespace bns
{
    class WebGPUBufferUtil final
    {
    public:
        /**
         * @brief Create a vertex buffer
         * @param device The webgpu device
         * @param data The data to be copied to the buffer
         * @param label The label of the buffer
         * @return The vertex buffer
         * @note The data is copied to the buffer
         */
        static WGPUBuffer CreateVertexBuffer(WGPUDevice device,
                                             std::vector<f32> data,
                                             std::string label);

        /**
         * @brief Create a index buffer
         * @param device The webgpu device
         * @param data The data to be copied to the buffer
         * @param label The label of the buffer
         * @return The index buffer
         * @note The data is copied to the buffer
         */
        static WGPUBuffer CreateIndexBuffer(WGPUDevice device,
                                            std::vector<u16> data,
                                            std::string label);

        /**
         * @brief Create a index buffer
         * @param device The webgpu device
         * @param data The data to be copied to the buffer
         * @param label The label of the buffer
         * @return The index buffer
         * @note The data is copied to the buffer
         */
        static WGPUBuffer CreateIndexBuffer(WGPUDevice device,
                                            std::vector<u32> data,
                                            std::string label);
    };
}

#endif