#if USE_METAL

#ifndef BNS_METAL_UNIFORM_BUFFER_HPP

#define BNS_METAL_UNIFORM_BUFFER_HPP

#include "buffers/bns_uniform_buffer.hpp"
#include "renderer/bns_metal_renderer.hpp"
#include "bns_metal_util.hpp"

namespace bns
{
    class MetalRenderer;

    /// @brief The Metal uniform buffer class.
    /// @tparam T The type of the uniform buffer.
    template <typename T>
    class MetalUniformBuffer : public UniformBuffer<T>
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
        MetalUniformBuffer(Renderer *renderer, std::string label = "")
            : UniformBuffer<T>()
        {
            m_renderer = static_cast<MetalRenderer *>(renderer);
            m_buffer = nullptr;
            m_label = label;
        }

        /// @brief Gets the buffer.
        inline MTL::Buffer *GetBuffer() const { return m_buffer; }

        /// @brief Initialize the constant buffer.
        void Initialize() override
        {
            m_buffer = MetalUtil::Buffer.Create(m_renderer->GetDevice(), sizeof(T), m_label);
        }

        /// @brief Update the constant buffer.
        void Update(T &data) override
        {
            void *contents = m_buffer->contents();
            memcpy(contents, &data, sizeof(T));
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
