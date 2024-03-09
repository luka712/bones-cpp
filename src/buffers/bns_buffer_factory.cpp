#include "buffers/bns_buffer_factory.hpp"

#if USE_OPENGL
#include "buffers/bns_opengl_index_buffer.hpp"
#endif 

namespace bns 
{
    IndexBuffer *BufferFactory::CreateIndexBuffer(std::vector<u16> data, std::string label)
    {
        return nullptr;
    }
}