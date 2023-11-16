#if USE_OPENGLES

#ifndef BNS_OpenGLES_BUFFER_UTIL_HPP

#define BNS_OpenGLES_BUFFER_UTIL_HPP

#include "BnsOpenGLES.hpp"
#include "buffer_layout/BufferLayoutData.hpp"
#include "Types.hpp"
#include <vector>
#include <exception>

namespace bns
{
    class OpenGLESBufferUtil
    {
    public:
        /// @brief Creates a vertex buffer
        /// @param data The data to be copied to the buffer
        /// @param usage The usage of the buffer. One of GL_STATIC_DRAW, GL_DYNAMIC_DRAW, GL_STREAM_DRAW. By default it is GL_STATIC_DRAW
        /// @return The vertex buffer
        static GLuint CreateVertexBuffer(std::vector<f32> data, GLenum usage = GL_STATIC_DRAW);

        /// @brief Creates a vertex buffer
        /// @param byteSize The size of the buffer in bytes
        /// @param usage The usage of the buffer. One of GL_STATIC_DRAW, GL_DYNAMIC_DRAW, GL_STREAM_DRAW. By default it is GL_STATIC_DRAW
        /// @return The vertex buffer
        static GLuint CreateVertexBuffer(size_t byteSize, GLenum usage = GL_STATIC_DRAW);

        /// @brief Create an OpenGLES index buffer
        /// @tparam T - the type of data. Usually should be u16 or u32
        /// @param data The data to be copied to the buffer
        /// @return The index buffer
        template <typename T>
        static GLuint CreateIndexBuffer(std::vector<T> data)
        {
            GLuint buffer;
            glGenBuffers(1, &buffer);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(T), data.data(), GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            return buffer;
        }

        /// @brief Creates a constant buffer
        /// @param byteSize The size of the buffer in bytes
        /// @param usage The usage of the buffer. One of GL_STATIC_DRAW, GL_DYNAMIC_DRAW, GL_STREAM_DRAW. By default it is GL_STATIC_DRAW
        /// @return The constant buffer
        static GLuint CreateConstantBuffer(size_t byteSize, GLenum usage = GL_STATIC_DRAW);

        /// @brief Creates a vertex array object.
        /// @param descriptors The buffer layout descriptors.
        /// @param outGLBuffers The buffer ids. The count of the buffers must be equal to the count of the descriptors.
        /// @param usage The usage of the buffer. One of GL_STATIC_DRAW, GL_DYNAMIC_DRAW, GL_STREAM_DRAW. By default it is GL_STATIC_DRAW
        /// @return The vertex array object id.
        static void CreateVertexBuffers(const std::vector<BufferLayoutDescriptor> &descriptors, std::vector<GLuint> &outGLBuffers, GLenum usage = GL_STATIC_DRAW);

        /// @brief Creates a vertex array object.
        /// @param descriptors The buffer layout descriptors.
        /// @param outGLBuffers The buffer ids. The count of the buffers must be equal to the count of the descriptors.
        /// @param usage The usage of the buffer. One of GL_STATIC_DRAW, GL_DYNAMIC_DRAW, GL_STREAM_DRAW. By default it is GL_STATIC_DRAW
        /// @return The vertex array object id.
        static void CreateVertexBuffers(const std::vector<BufferLayoutDescriptor> &descriptors, GLuint *outGLBuffers, GLenum usage = GL_STATIC_DRAW);

        /// @brief Converts the vertex format to OpenGLES vertex format.
        /// @param format The vertex format.
        /// @param outType The OpenGLES vertex format.
        /// @param outSize The OpenGLES vertex format.
        /// @param outNormalized The OpenGLES vertex format.
        /// @return The OpenGLES vertex format.
        static void Convert(VertexFormat format, GLenum *outType, GLint *outSize, GLboolean *outNormalized);
    };
}

#endif

#endif // USE_OpenGLES