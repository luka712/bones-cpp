#if USE_OPENGL

#include "util/OpenGLProgramUtil.hpp"
#include "bns_types.hpp"
#include <stdexcept>
#include <string>

namespace bns
{
    GLuint OpenGLProgramUtil::Create(GLuint vertexShader, GLuint fragmentShader)
    {
        GLuint program = glCreateProgram();
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);

        GLint success;
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success)
        {
            GLchar infoLog[512];
            glGetProgramInfoLog(program, 512, nullptr, infoLog);
            std::string msg = "OpenGLProgramUtil::Create: Failed to link program: " + std::string(infoLog);

            glDeleteProgram(program);

            LOG(msg.c_str());
            BREAKPOINT();
            throw std::runtime_error(msg.c_str());
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return program;
    }

    GLint OpenGLProgramUtil::GetUniformLocation(GLuint program, std::string name)
    {
        GLint location = glGetUniformLocation(program, name.c_str());

        if (location == -1)
        {
            std::string msg = "OpenGLProgramUtil::GetUniformLocation: Failed to get uniform location: " + name;
            LOG(msg.c_str());
            BREAKPOINT();
            throw std::runtime_error(msg.c_str());
        }
    }
}
#endif
