#if USE_WEBGPU

#ifndef BNS_WEBGPU_UNIFORM_BUFFER_HPP

#define BNS_WEBGPU_UNIFORM_BUFFER_HPP

#include "buffers/bns_uniform_buffer.hpp"
#include "renderer/bns_webgpu_renderer.hpp"
#include <string>
#include "bns_webgpu_util.hpp"

namespace bns
{
    /// @brief The webgpu uniform buffer.
    template <typename T>
    class WebGPUUniformBuffer : public UniformBuffer<T>
    {
    private:
        WGPUDevice m_device;
        WGPUQueue m_queue;
        WGPUBuffer m_uniformBuffer;
        std::string m_label;

    public:
        /// @brief The constructor for the constant buffer.
        /// @param renderer The renderer.
        /// @param label The label of the buffer. By default, it is empty.
        WebGPUUniformBuffer(Renderer *renderer, std::string label = "")
        {
            m_device = static_cast<WebGPURenderer *>(renderer)->GetDevice();
            m_queue = static_cast<WebGPURenderer *>(renderer)->GetQueue();
            m_label = label;
        }

        /// @brief Destructor for the constant buffer.
        ~WebGPUUniformBuffer()
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