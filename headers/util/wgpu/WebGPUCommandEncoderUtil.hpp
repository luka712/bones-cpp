#ifndef BNS_WEBGPU_COMMAND_ENCODER_HPP

#define BNS_WEBGPU_COMMAND_ENCODER_HPP

#include <webgpu/webgpu.h>
#include <string>

namespace bns
{
    struct WebGPUCommandEncoderUtil
    {
        /// @brief Create a command encoder with default descriptor.
        /// @param device - The device.
        /// @param label - The label for command encoder descriptor.
        /// @return The command encoder.
        static WGPUCommandEncoder Create(WGPUDevice device, std::string label = "command_encoder");

        /// @brief Create a command encoder.
        /// @param device The device.
        /// @param descriptor The descriptor.
        /// @return The command encoder.
        static WGPUCommandEncoder Create(WGPUDevice device, WGPUCommandEncoderDescriptor &descriptor);
    };
}

#endif