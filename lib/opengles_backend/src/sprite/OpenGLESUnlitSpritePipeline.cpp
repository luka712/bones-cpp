#if USE_OPENGLES

#include "sprite/OpenGLESUnlitSpritePipeline.hpp"
#include "OpenGLESUtil.hpp"

namespace bns
{
    OpenGLESUnlitSpritePipeline::OpenGLESUnlitSpritePipeline(GLuint program,
                                                         GLint textureLocation,
                                                         OpenGLESTexture2D *texture)
        : m_program(program),
          m_textureLocation(textureLocation),
          m_texture(texture),
          InstanceIndex(0)
    {
    }

    OpenGLESUnlitSpritePipeline::~OpenGLESUnlitSpritePipeline()
    {
        Release();
    }

    OpenGLESUnlitSpritePipeline *OpenGLESUnlitSpritePipeline::Create(OpenGLESTexture2D *texture)
    {
        GLuint vertexShader = OpenGLESUtil::Shader.CreateVertexShader("shaders/opengles/sprite/unlit_sprite_vs.glsl");
        GLuint fragmentShader = OpenGLESUtil::Shader.CreateFragmentShader("shaders/opengles/sprite/unlit_sprite_fs.glsl");

        GLuint program = OpenGLESUtil::Program.Create(vertexShader, fragmentShader);
        GLint textureLocation = OpenGLESUtil::Program.GetUniformLocation(program, "u_texture");

        return new OpenGLESUnlitSpritePipeline(program, textureLocation, texture);
    }

    void OpenGLESUnlitSpritePipeline::Release()
    {
        glDeleteProgram(m_program);
        m_program = 0;
    }
}

#endif