#if USE_OPENGL

#include "util/OpenGLVAOUtil.hpp"
#include <string>
#include "OpenGLUtil.hpp"

namespace bns
{
    void OpenGLVAOUtil::Convert(VertexFormat vertexFormat, GLenum *outType, GLint *outSize, GLboolean *outNormalized)
    {
        return OpenGLUtil::Buffer.Convert(vertexFormat, outType, outSize, outNormalized);
    }

    GLuint OpenGLVAOUtil::Create(const std::vector<BufferLayoutDescriptor> &descriptors, GLuint *outBuffers, GLenum usage)
    {
        GLuint vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        OpenGLUtil::Buffer.CreateVertexBuffers(descriptors, outBuffers, usage);

        glBindVertexArray(0);

        return vao;
    }

    GLuint OpenGLVAOUtil::Create(const std::vector<BufferLayoutDescriptor> &descriptors, std::vector<GLuint> &outBuffers, GLenum usage)
    {
        return Create(descriptors, outBuffers.data(), usage);
    }
}

#endif