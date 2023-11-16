#if USE_OPENGLES

#include "util/OpenGLESVAOUtil.hpp"
#include <string>
#include "OpenGLESUtil.hpp"

namespace bns
{
    void OpenGLESVAOUtil::Convert(VertexFormat vertexFormat, GLenum *outType, GLint *outSize, GLboolean *outNormalized)
    {
        return OpenGLESUtil::Buffer.Convert(vertexFormat, outType, outSize, outNormalized);
    }

    GLuint OpenGLESVAOUtil::Create(const std::vector<BufferLayoutDescriptor> &descriptors, GLuint *outBuffers, GLenum usage)
    {
        GLuint vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        OpenGLESUtil::Buffer.CreateVertexBuffers(descriptors, outBuffers, usage);

        glBindVertexArray(0);

        return vao;
    }

    GLuint OpenGLESVAOUtil::Create(const std::vector<BufferLayoutDescriptor> &descriptors, std::vector<GLuint> &outBuffers, GLenum usage)
    {
        return Create(descriptors, outBuffers.data(), usage);
    }
}

#endif