#if USE_OPENGL

#include "sprite/400/OpenGL400UnlitSpritePipeline.hpp"
#include "bns_opengl_util.hpp"

namespace bns
{
    OpenGL400UnlitSpritePipeline::OpenGL400UnlitSpritePipeline(GLuint program,
                                                               GLint textureLocation,
                                                               GLint projectionViewLocation,
                                                               OpenGLTexture2D *texture)
        : m_program(program),
          m_textureLocation(textureLocation),
          m_projectionViewLocation(projectionViewLocation),
          m_texture(texture),
          InstanceIndex(0)
    {
    }

    OpenGL400UnlitSpritePipeline::~OpenGL400UnlitSpritePipeline()
    {
        Release();
    }

    OpenGL400UnlitSpritePipeline *OpenGL400UnlitSpritePipeline::Create( OpenGLTexture2D *texture)
    {
        GLuint vertexShader = OpenGLUtil::Shader.CreateVertexShader("shaders/opengl/sprite/400/unlit_sprite_vs.glsl");
        GLuint fragmentShader = OpenGLUtil::Shader.CreateFragmentShader("shaders/opengl/sprite/400/unlit_sprite_fs.glsl");

        GLuint program = OpenGLUtil::Program.Create(vertexShader, fragmentShader);
        GLint textureLocation = OpenGLUtil::Program.GetUniformLocation(program, "u_texture");
        GLint projectionViewLocation = OpenGLUtil::Program.GetUniformLocation(program, "u_projectionViewMatrix");

        return new OpenGL400UnlitSpritePipeline(program, textureLocation, projectionViewLocation, texture);
    }

    void OpenGL400UnlitSpritePipeline::Release()
    {
        glDeleteProgram(m_program);
        m_program = 0;
    }
}

#endif
