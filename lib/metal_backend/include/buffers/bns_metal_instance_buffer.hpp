#if USE_METAL

#ifndef BNS_METAL_INSTANCE_BUFFER_HPP

#define BNS_METAL_INSTANCE_BUFFER_HPP

#include "buffers/bns_instance_buffer.hpp"
#include "renderer/bns_metal_renderer.hpp"
#include "bns_metal_util.hpp"

namespace bns
{
    class MetalRenderer;

    /// @brief The Metal uniform buffer class.
    /// @tparam T The type of the uniform buffer.
    template <typename T>
    class MetalInstanceBuffer : public InstanceBuffer<T>
    {
    private:
        MTL::Buffer *m_buffer;
        MetalRenderer *m_renderer;
        std::string m_label;

    public:
        /// @brief The constructor.
        /// @param renderer The renderer.
        /// @param instanceCount The instance count. For instanced rendering.
        /// @param label The label.
        MetalInstanceBuffer(Renderer *renderer, i32 instanceCount = 1, std::string label = "")
            : InstanceBuffer<T>(label, instanceCount)
        {
            m_renderer = static_cast<MetalRenderer *>(renderer);
            m_buffer = nullptr;
            m_label = label;
        }

        /// @brief Gets the buffer.
        inline MTL::Buffer *GetBuffer() const { return m_buffer; }

        /// @brief Initialize the constant buffer.
        void Initialize(std::vector<T> &data, bool isWritable = false) override
        {
            if(isWritable)
            {
                m_renderer->OnBlitCommandEncoderAvailable([this, &data](MTL::BlitCommandEncoder *blitCommandEncoder)
                {
                    m_buffer = MetalUtil::Buffer.CreateWithGPUOnlyAccess(blitCommandEncoder, m_renderer->GetDevice(), data, m_label);
                });
            }
            else
            {
                m_buffer = MetalUtil::Buffer.Create(m_renderer->GetDevice(),data, m_label);
            }
        }

        /// @brief Update the constant buffer.
        void Update(std::vector<T> &data, i32 instance = 1) override
        {
            void *contents = m_buffer->contents();
            memcpy(contents, &data, sizeof(T) * instance);
        }
       
        /// @brief Dispose the constant buffer.
        void Dispose() override
        {
            m_buffer->release();
        }
    };
}

#endif

#endif
