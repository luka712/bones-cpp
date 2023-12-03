#if USE_OPENGL

#include "util/OpenGLShaderUtil.hpp"
#include "FileLoader.hpp"
#include <stdexcept>
#include "Types.hpp"

namespace bns 
{
    GLuint OpenGLShaderUtil::Create(std::string filePath, GLenum shaderType)
    {
        FileLoader fileLoader;
        std::string shaderSource = fileLoader.LoadFile(filePath);
        const char *shaderSourcePtr = shaderSource.c_str();

        GLuint shader = glCreateShader(shaderType);
        glShaderSource(shader, 1, &shaderSourcePtr, nullptr);
        glCompileShader(shader);

        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            GLchar infoLog[512];
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            std::string msg = "OpenGLShaderUtil::Create: Failed to compile shader: " + std::string(infoLog);

            glDeleteShader(shader);

            LOG("%s", msg.c_str());
            BREAKPOINT();
            throw std::runtime_error(msg.c_str());
        }

        return shader;
    }

    GLuint OpenGLShaderUtil::CreateVertexShader(std::string filePath)
    {
        return Create(filePath, GL_VERTEX_SHADER);
    }

    GLuint OpenGLShaderUtil::CreateFragmentShader(std::string filePath)
    {
        return Create(filePath, GL_FRAGMENT_SHADER);
    }
}

#endif 
