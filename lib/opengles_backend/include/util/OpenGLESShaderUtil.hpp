#if USE_OPENGLES

#ifndef BNS_OpenGLES_SHADER_UTIL_HPP

#define BNS_OpenGLES_SHADER_UTIL_HPP

#include "BnsOpenGLES.hpp"
#include <string>

namespace bns 
{
    class OpenGLESShaderUtil
    {
    public:
        /// @brief Create a shader from a file.
        /// @param filePath The filepath.
        /// @param shaderType The shader type. One of GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, GL_GEOMETRY_SHADER, GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER, GL_COMPUTE_SHADER.
        /// @return The shader id.
        static GLuint Create(std::string filePath, GLenum shaderType);

        /// @brief Creates a vertex shader.
        /// @param filePath The file path.
        /// @return The shader id.
        static GLuint CreateVertexShader(std::string filePath);

        /// @brief Creates a fragment shader.
        /// @param filePath The file path.
        /// @return The shader id.
        static GLuint CreateFragmentShader(std::string filePath);

    };

}

#endif // !BNS_OpenGLES_SHADER_UTIL_HPP
#endif // USE_OpenGLES