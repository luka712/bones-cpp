#if USE_OPENGLES

#include "util/OpenGLESBufferUtil.hpp"
#include <stdexcept>
#include "OpenGLESUtil.hpp"

namespace bns
{
    GLuint OpenGLESBufferUtil::CreateConstantBuffer(size_t byteSize, GLenum usage)
    {
        GLuint buffer;
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_UNIFORM_BUFFER, buffer);
        glBufferData(GL_UNIFORM_BUFFER, byteSize, nullptr, usage);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
        return buffer;
    }

    GLuint OpenGLESBufferUtil::CreateVertexBuffer(std::vector<f32> data, GLenum usage)
    {
        GLuint buffer;
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(f32), data.data(), usage);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        return buffer;
    }

    GLuint OpenGLESBufferUtil::CreateVertexBuffer(size_t byteSize, GLenum usage)
    {
        GLuint buffer;
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, byteSize, nullptr, usage);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        return buffer;
    }

    void OpenGLESBufferUtil::Convert(VertexFormat vertexFormat, GLenum *outType, GLint *outSize, GLboolean *outNormalized)
    {
        switch (vertexFormat)
        {
        case VertexFormat::Float32x2:
            *outType = GL_FLOAT;
            *outSize = 2;
            *outNormalized = GL_FALSE;
            break;
        case VertexFormat::Float32x3:
            *outType = GL_FLOAT;
            *outSize = 3;
            *outNormalized = GL_FALSE;
            break;
        case VertexFormat::Float32x4:
            *outType = GL_FLOAT;
            *outSize = 4;
            *outNormalized = GL_FALSE;
            break;
        default:
            std::string msg = "OpenGLESVAOUtil::Convert: Invalid vertex format " + std::to_string((int)vertexFormat) + ".";
            LOG(msg.c_str());
            throw std::runtime_error(msg.c_str());
        }
    }

    void OpenGLESBufferUtil::CreateVertexBuffers(const std::vector<BufferLayoutDescriptor> &descriptors, GLuint *outBuffers, GLenum usage)
    {
        // VALIDATION STEP FIRST
        for (auto desc : descriptors)
        {
            if (desc.ByteSize == 0)
            {
                std::string msg = "OpenGLESVAOUtil::CreateVertexBuffers: Invalid byte size " + std::to_string(desc.ByteSize) + ".";
                LOG(msg.c_str());
                BREAKPOINT();
                throw std::runtime_error(msg.c_str());
            }
        }

        // Now buffers

        GLint attributeIndex = 0;

        for (size_t i = 0; i < descriptors.size(); i++)
        {
            BufferLayoutDescriptor descriptor = descriptors[i];

            GLuint buffer;
            glGenBuffers(1, &buffer);
            glBindBuffer(GL_ARRAY_BUFFER, buffer);
            glBufferData(GL_ARRAY_BUFFER, descriptor.ByteSize, descriptor.Data, usage);

            for (size_t j = 0; j < descriptor.Attributes.size(); j++)
            {
                BufferLayoutAttributeDescriptor attr = descriptor.Attributes[j];

                GLenum type;
                GLint size;
                GLboolean normalized;
                Convert(attr.Format, &type, &size, &normalized);

                glEnableVertexAttribArray(attr.ShaderLocation);
                glVertexAttribPointer(attr.ShaderLocation, size, type, normalized, descriptor.Stride, (void *)attr.Offset);
            }

            outBuffers[0] = buffer;
        }

        // unbind any buffer
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void OpenGLESBufferUtil::CreateVertexBuffers(const std::vector<BufferLayoutDescriptor> &descriptors, std::vector<GLuint> &outBuffers, GLenum usage)
    {
        CreateVertexBuffers(descriptors, outBuffers.data(), usage);
    }

}

#endif
