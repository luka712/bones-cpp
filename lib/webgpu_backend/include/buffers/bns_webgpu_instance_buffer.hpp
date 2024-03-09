#if USE_WEBGPU

#ifndef BNS_WEBGPU_INSTANCES_BUFFER_HPP

#define BNS_WEBGPU_INSTANCES_BUFFER_HPP

#include "buffers/bns_instance_buffer.hpp"
#include "bns_webgpu.hpp"

namespace bns 
{
    /// @brief The webgpu instances buffer.
    template <typename T>
    class WebGPUInstanceBuffer : public InstanceBuffer<T>
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
        WebGPUInstanceBuffer(Renderer *renderer, u32 instanceCount = 1, std::string label = "")
            : InstanceBuffer<T>(instanceCount, label)
        {
            m_device = static_cast<WebGPURenderer *>(renderer)->GetDevice();
            m_queue = static_cast<WebGPURenderer *>(renderer)->GetQueue();
        }

        /// @brief Destructor for the constant buffer.
        ~WebGPUInstanceBuffer()
        {
            Dispose();
        }

        WGPUBuffer GetBuffer() const
        {
            return m_uniformBuffer;
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
            WebGPUUtil::Buffer.UpdateUniformBuffer(m_queue, m_uniformBuffer, sizeof(T), &data);
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