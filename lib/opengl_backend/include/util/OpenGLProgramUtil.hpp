#if USE_OPENGL

#ifndef BNS_OPENGL_PROGRAM_UTIL_HPP

#define BNS_OPENGL_PROGRAM_UTIL_HPP

#include "bns_opengl.hpp"
#include <string>

namespace bns
{
    struct OpenGLProgramUtil
    {
        /// @brief Create a program.
        /// @param vertexShader The vertex shader id.
        /// @param fragmentShader The fragment shader id.
        /// @return The program id.
        static GLuint Create(GLuint vertexShader, GLuint fragmentShader);

        /// @brief Gets the uniform location.
        /// @param program The program id.
        /// @param name The uniform name.
        /// @return The uniform location.
        static GLint GetUniformLocation(GLuint program, std::string name);
    };
}

#endif // !BNS_OPENGL_PROGRAM_UTIL_HPP

#endif // USE_OPENGL