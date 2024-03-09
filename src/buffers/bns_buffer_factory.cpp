#include "buffers/bns_buffer_factory.hpp"
#include "Framework.hpp"

#if USE_OPENGL
    #include "buffers/bns_opengl_index_buffer.hpp"
    #include "buffers/bns_opengl_vertex_buffer.hpp"
#endif 

#if USE_WEBGPU
    #include "buffers/bns_webgpu_index_buffer.hpp"
    #include "buffers/bns_webgpu_vertex_buffer.hpp"
#endif

namespace bns 
{
    BufferFactory::BufferFactory(Framework *framework)
    : m_framework(framework)
    {
    }

    IndexBuffer *BufferFactory::CreateIndexBuffer(std::vector<u16> data, std::string label)
    {
        IndexBuffer *indexBuffer = nullptr;
        RendererType rendererType = m_framework->GetRendererType();
        
        #if USE_OPENGL
        if(rendererType == RendererType::OpenGL)
        {
            indexBuffer = new OpenGLIndexBuffer(label);
        }
        #endif 

        #if USE_WEBGPU
        if(rendererType == RendererType::WebGPU)
        {
            indexBuffer = new WebGPUIndexBuffer(m_framework->GetRenderer(), label);
        }
        #endif

        indexBuffer->Initialize(data);
        return indexBuffer;
    }

    VertexBuffer *BufferFactory::CreateVertexBuffer(std::vector<f32> data, std::string label)
    {
        VertexBuffer *vertexBuffer = nullptr;
        RendererType rendererType = m_framework->GetRendererType();
        
        #if USE_OPENGL
        if(rendererType == RendererType::OpenGL)
        {
            vertexBuffer = new OpenGLVertexBuffer(label);
        }
        #endif 

        #if USE_WEBGPU
        if(rendererType == RendererType::WebGPU)
        {
            vertexBuffer = new WebGPUVertexBuffer(m_framework->GetRenderer(), label);
        }
        #endif

        vertexBuffer->Initialize(data);
        return vertexBuffer;
    }
}