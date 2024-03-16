#if USE_OPENGL

#ifndef BNS_OPENGL_CONVERTER_HPP

#define BNS_OPENGL_CONVERTER_HPP

#include "bns_opengl.hpp"
#include "bns_rendering_backend_types.hpp"

namespace bns
{
    struct OpenGLConverter
    {
        /// @brief Converts the vertex format to OpenGL vertex format.
        /// @param format The vertex format.
        /// @return The OpenGL vertex format which is number of components.
        static size_t Convert(VertexFormat format);
    };
}

#endif 

#endif 