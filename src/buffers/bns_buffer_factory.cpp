#include "buffers/bns_buffer_factory.hpp"
#include "bns_framework.hpp"

#if USE_OPENGL
#include "buffers/bns_opengl_index_buffer.hpp"
#include "buffers/bns_opengl_vertex_buffer.hpp"
#endif

#if USE_WEBGPU
#include "buffers/bns_webgpu_index_buffer.hpp"
#include "buffers/bns_webgpu_vertex_buffer.hpp"
#endif

#if USE_METAL
#include "buffers/bns_metal_index_buffer.hpp"
#include "buffers/bns_metal_vertex_buffer.hpp"
#endif

namespace bns
{
    BufferFactory::BufferFactory(Renderer *renderer)
        : m_renderer(renderer)
    {
    }

    IndexBuffer *BufferFactory::CreateIndexBuffer(std::vector<u16> &data, std::string label)
    {
        IndexBuffer *indexBuffer = nullptr;
        RendererType rendererType = m_renderer->GetRendererType();

#if USE_OPENGL
        if (rendererType == RendererType::OpenGL)
        {
            indexBuffer = new OpenGLIndexBuffer(label);
        }
#endif

#if USE_WEBGPU
        if (rendererType == RendererType::WebGPU)
        {
            indexBuffer = new WebGPUIndexBuffer(m_renderer, label);
        }
#endif
        
#if USE_METAL
       if(rendererType == RendererType::Metal)
       {
           indexBuffer = new MetalIndexBuffer(m_renderer, label);
       }
#endif

        indexBuffer->Initialize(data);
        return indexBuffer;
    }

    VertexBuffer *BufferFactory::CreateVertexBuffer(std::vector<f32> &data, std::string label)
    {
        VertexBuffer *vertexBuffer = nullptr;
        RendererType rendererType = m_renderer->GetRendererType();

#if USE_OPENGL
        if (rendererType == RendererType::OpenGL)
        {
            vertexBuffer = new OpenGLVertexBuffer(label);
        }
#endif

#if USE_WEBGPU
        if (rendererType == RendererType::WebGPU)
        {
            vertexBuffer = new WebGPUVertexBuffer(m_renderer, label);
        }
#endif
        
#if USE_METAL
        if (rendererType == RendererType::Metal)
        {
            vertexBuffer = new MetalVertexBuffer(m_renderer, label);
        }
#endif

        vertexBuffer->Initialize(data);
        return vertexBuffer;
    }
}
