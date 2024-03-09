#if USE_OPENGL

#include "sprite/OpenGLUnlitSpritePipeline.hpp"
#include "bns_opengl_util.hpp"

namespace bns
{
    OpenGLUnlitSpritePipeline::OpenGLUnlitSpritePipeline(GLuint program,
                                                         GLint textureLocation,
                                                         OpenGLTexture2D *texture)
        : m_program(program),
          m_textureLocation(textureLocation),
          m_texture(texture),
          InstanceIndex(0)
    {
    }

    OpenGLUnlitSpritePipeline::~OpenGLUnlitSpritePipeline()
    {
        Release();
    }

    OpenGLUnlitSpritePipeline *OpenGLUnlitSpritePipeline::Create(OpenGLTexture2D *texture)
    {
        GLuint vertexShader = OpenGLUtil::Shader.CreateVertexShader("shaders/opengl/sprite/unlit_sprite_vs.glsl");
        GLuint fragmentShader = OpenGLUtil::Shader.CreateFragmentShader("shaders/opengl/sprite/unlit_sprite_fs.glsl");

        GLuint program = OpenGLUtil::Program.Create(vertexShader, fragmentShader);
        GLint textureLocation = OpenGLUtil::Program.GetUniformLocation(program, "u_texture");

        return new OpenGLUnlitSpritePipeline(program, textureLocation, texture);
    }

    void OpenGLUnlitSpritePipeline::Release()
    {
        glDeleteProgram(m_program);
        m_program = 0;
    }
}

#endif