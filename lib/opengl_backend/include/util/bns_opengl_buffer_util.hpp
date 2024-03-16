#if USE_OPENGL

#ifndef BNS_OPENGL_BUFFER_UTIL_HPP

#define BNS_OPENGL_BUFFER_UTIL_HPP

#include "bns_opengl.hpp"
#include "buffer_layout/BufferLayoutData.hpp"
#include "bns_types.hpp"
#include <vector>
#include <exception>

namespace bns
{
	class OpenGLBufferUtil
	{
	public:
		/// @brief Creates a vertex buffer
		/// @param data The data to be copied to the buffer
		/// @param usage The usage of the buffer. One of GL_STATIC_DRAW, GL_DYNAMIC_DRAW, GL_STREAM_DRAW. By default it is GL_STATIC_DRAW.
		/// @param label The label of the buffer. By default it is "".
		/// @return The vertex buffer
		template <typename T>
		static GLuint CreateVertexBuffer(std::vector<T>& data, GLenum usage = GL_STATIC_DRAW, std::string label = "")
		{
			GLuint buffer;
			glGenBuffers(1, &buffer);
			glBindBuffer(GL_ARRAY_BUFFER, buffer);
			glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(T), data.data(), usage);
			if (label.length() > 0)
			{
				glObjectLabel(GL_BUFFER, buffer, label.length(), label.c_str());
			}
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			return buffer;
		}

		/// @brief Creates a vertex buffer
		/// @param byteSize The size of the buffer in bytes
		/// @param usage The usage of the buffer. One of GL_STATIC_DRAW, GL_DYNAMIC_DRAW, GL_STREAM_DRAW. By default it is GL_STATIC_DRAW.
		/// @param label The label of the buffer. By default it is "".
		/// @return The vertex buffer
		static GLuint CreateVertexBuffer(size_t byteSize, GLenum usage = GL_STATIC_DRAW, std::string label = "");

		/// @brief Writes to a vertex buffer.
		/// @param buffer The buffer to write to.
		/// @param byteSize The size of the data in bytes.
		/// @param data The data to be copied to the buffer.
		/// @param offset The offset to write data. By default 0. This is in bytes of the buffer.
		static void WriteVertexBuffer(GLuint buffer, size_t byteSize, std::vector<f32> data, u32 offset = 0);

		/// @brief Create an OpenGL index buffer.
		/// @tparam T - the type of data. Usually should be u16 or u32.
		/// @param data The data to be copied to the buffer.
		/// @param label The label of the buffer. By default it is "".
		/// @return The index buffer.
		template <typename T>
		static GLuint CreateIndexBuffer(std::vector<T>& data, std::string label = "")
		{
			GLuint buffer;
			glGenBuffers(1, &buffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(T), data.data(), GL_STATIC_DRAW);

			if (label.length() > 0)
			{
				glObjectLabel(GL_BUFFER, buffer, label.length(), label.c_str());
			}

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

			return buffer;
		}

		/// @brief Creates a uniform buffer.
		/// @param byteSize The size of the buffer in bytes.
		/// @param label The label of the buffer. By default it is "".
		/// @param usage The usage of the buffer. One of GL_STATIC_DRAW, GL_DYNAMIC_DRAW, GL_STREAM_DRAW. By default it is GL_STATIC_DRAW.
		/// @return The constant buffer.
		static GLuint CreateUniformBuffer(size_t byteSize, std::string label = "", GLenum usage = GL_STATIC_DRAW);

		/// @brief Writes to a uniform buffer.
		/// @param buffer The buffer to write to.
		/// @param data The pointer to data to be copied to the buffer.
		template <typename T>
		static void WriteUniformBuffer(GLuint buffer, T *data)
		{
			glBindBuffer(GL_UNIFORM_BUFFER, buffer);
			glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(T), data);
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
		}

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

		/// @brief Converts the vertex format to OpenGL vertex format.
		/// @param format The vertex format.
		/// @param outType The OpenGL vertex format.
		/// @param outSize The OpenGL vertex format.
		/// @param outNormalized The OpenGL vertex format.
		/// @return The OpenGL vertex format.
		static void Convert(VertexFormat format, GLenum *outType, GLint *outSize, GLboolean *outNormalized);

		/// @brief Disposes the buffer.
		static void Dispose(GLuint buffer);
	};
}

#endif

#endif // USE_OPENGL