#if USE_OPENGL

#include "util/bns_opengl_texture_util.hpp"
#include "bns_opengl_util.hpp"

namespace bns
{
    GLuint OpenGLTextureUtil::CreateTexture2D(
        u32 width, u32 height,
        void *data,
        std::string label,
        TextureFormat format,
        SamplerMinFilter minFilter,
        SamplerMagFilter magFilter)
    {

        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        // Convert from bones types to OpenGL types.
        GLenum glFormat = OpenGLUtil::Converter.Convert(format);
        GLenum glMinFilter = OpenGLUtil::Converter.Convert(minFilter);
        GLenum glMagFilter = OpenGLUtil::Converter.Convert(magFilter);

        // Set texture.
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, glFormat, GL_UNSIGNED_BYTE, data);

        // Set parameters.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, glMinFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, glMagFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // Set label.
        if (label != "")
        {
            glObjectLabel(GL_TEXTURE, texture, label.size(), label.c_str());
        }

        return texture;
    }

}

#endif