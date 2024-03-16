#if USE_OPENGL

#include "util/bns_opengl_converter.hpp"
#include "bns_types.hpp"
#include <stdexcept>
#include <string>

namespace bns
{

    /// @brief Converts the vertex format to OpenGL vertex format.
    /// @param format The vertex format.
    /// @return The OpenGL vertex format which is number of components.
    size_t OpenGLConverter::Convert(VertexFormat format)
    {
        switch (format)
        {
        case VertexFormat::Float32x1:
            return 1;
        case VertexFormat::Float32x2:
            return 2;
        case VertexFormat::Float32x3:
            return 3;
        case VertexFormat::Float32x4:
            return 4;
        default:
            std::string msg = "OpenGLConverter::Convert: Invalid vertex format " + std::to_string((int)format) + ".";
            LOG(msg);
            BREAKPOINT();
            throw std::runtime_error(msg);
        }
    }
}

#endif