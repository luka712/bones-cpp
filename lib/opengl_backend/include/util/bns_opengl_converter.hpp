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

        /// @brief Converts the texture format to OpenGL texture format.
        /// @param format The texture format.
        /// @return The OpenGL texture format.
        static GLenum Convert(TextureFormat format);

        /// @brief Converts the sampler min filter to OpenGL sampler min filter.
        /// @param filter The sampler min filter.
        /// @return The OpenGL sampler min filter.
        static GLenum Convert(SamplerMinFilter filter);

        /// @brief Converts the sampler mag filter to OpenGL sampler mag filter.
        /// @param filter The sampler mag filter.
        /// @return The OpenGL sampler mag filter.
        static GLenum Convert(SamplerMagFilter filter);
    };
}

#endif 

#endif 