#if USE_OPENGL

#ifndef BNS_OPENGL_VERTEX_ARRAY_OBJECT_UTIL_HPP

#define BNS_OPENGL_VERTEX_ARRAY_OBJECT_UTIL_HPP

#include "bns_opengl.hpp"
#include "buffer_layout/BufferLayoutData.hpp"
#include <string>

namespace bns
{
    struct OpenGLBufferLayoutDescriptor
    {
        /// @brief The buffer layout descriptor.
        BufferLayoutDescriptor BufferLayoutDescriptor;

        /// @brief The buffer id.
        GLuint Buffer;

        /// @brief Is buffer instanced.
        bool IsInstanced;
    };

    /// @brief The vertex array object util.
    struct OpenGLVertexArrayObjectUtil
    {
        /// @brief Creates a vertex array object.
        /// @param label The label.
        /// @param unbind Unbind the vertex array object.
        /// @return The vertex array object id.
        static GLuint Create(std::string label = "", bool unbind = false);

        /// @brief Creates a vertex array object.
        /// @param descriptors The buffer layout descriptors.
        /// @param label The label.
        /// @return The vertex array object id.
        static GLuint Create(const std::vector<OpenGLBufferLayoutDescriptor> &descriptors, std::string label = "");
    };
}

#endif

#endif