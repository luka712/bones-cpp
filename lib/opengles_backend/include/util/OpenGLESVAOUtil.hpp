#if USE_OPENGLES

#ifndef BNS_OpenGLES_VAO_UTIL_HPP

#define BNS_OpenGLES_VAO_UTIL_HPP

#include "BnsOpenGLES.hpp"
#include <map>
#include "buffer_layout/BufferLayoutData.hpp"

namespace bns
{
    struct OpenGLESVAOUtil
    {
        /// @brief Creates a vertex array object.
        /// @param descriptors The buffer layout descriptors.
        /// @param outGLBuffers The buffer ids. The count of the buffers must be equal to the count of the descriptors.
        /// @param usage The usage of the buffer. One of GL_STATIC_DRAW, GL_DYNAMIC_DRAW, GL_STREAM_DRAW. By default it is GL_STATIC_DRAW
        /// @return The vertex array object id.
        static GLuint Create(const std::vector<BufferLayoutDescriptor> &descriptors, std::vector<GLuint> &outGLBuffers, GLenum usage = GL_STATIC_DRAW);

        /// @brief Creates a vertex array object.
        /// @param descriptors The buffer layout descriptors.
        /// @param outGLBuffers The buffer ids. The count of the buffers must be equal to the count of the descriptors.
        /// @param usage The usage of the buffer. One of GL_STATIC_DRAW, GL_DYNAMIC_DRAW, GL_STREAM_DRAW. By default it is GL_STATIC_DRAW
        /// @return The vertex array object id.
        static GLuint Create(const std::vector<BufferLayoutDescriptor> &descriptors, GLuint *outGLBuffers, GLenum usage = GL_STATIC_DRAW);

        /// @brief Converts the vertex format to OpenGLES vertex format.
        /// @param format The vertex format.
        /// @param outType The OpenGLES vertex format.
        /// @param outSize The OpenGLES vertex format.
        /// @param outNormalized The OpenGLES vertex format.
        /// @return The OpenGLES vertex format.
        static void Convert(VertexFormat format, GLenum *outType, GLint *outSize, GLboolean *outNormalized);
    };
}

#endif // !BNS_OpenGLES_VAO_UTIL_HPP

#endif // USE_OpenGLES