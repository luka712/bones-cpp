#if USE_WEBGPU

#ifndef BNS_WEBGPU_CONSTANT_BUFFER_HPP

#define BNS_WEBGPU_CONSTANT_BUFFER_HPP

#include "constant_buffer/bns_constant_buffer.hpp"
#include "renderer/bns_webgpu_renderer.hpp"
#include <string>
#include "bns_webgpu_util.hpp"

namespace bns
{
    template <typename T>
    class WebGPUConstantBuffer : public ConstantBuffer<T>
    {
    private:
        WGPUDevice m_device;
        WGPUQueue m_queue;
        WGPUBuffer m_uniformBuffer;
        std::string m_label;

    public:
        /// @brief The constructor for the constant buffer.
        /// @param renderer The renderer.
        /// @param instanceCount The number of instances that buffer supoorts. 1 by default.
        /// @param label The label of the buffer. By default, it is empty.
        WebGPUConstantBuffer(Renderer *renderer, u32 instanceCount = 1, std::string label = "")
            : ConstantBuffer<T>(instanceCount)
        {
            m_device = static_cast<WebGPURenderer *>(renderer)->GetDevice();
            m_queue = static_cast<WebGPURenderer *>(renderer)->GetQueue();
            m_label = label;
        }
        ~WebGPUConstantBuffer()
        {
            Dispose();
        }

        void Initialize() override
        {
            m_uniformBuffer = WebGPUUtil::Buffer.CreateUniformBuffer(
                m_device,
                sizeof(T),
                "ConstantBuffer");
        }

        void Update(T &data) override
        {
            WebGPUUtil::Buffer.UpdateUniformBuffer(m_queue, m_uniformBuffer, sizeof(T), & data);
        } 

        void Dispose() override
        {
            if (m_uniformBuffer != nullptr)
            {
                WebGPUUtil::Buffer.Dispose(m_uniformBuffer);
                m_uniformBuffer = nullptr;
            }
        }
    };
}

#endif

#endif