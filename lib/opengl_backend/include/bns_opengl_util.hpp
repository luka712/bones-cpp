#if USE_OPENGL

#ifndef BNS_OPENGL_UTIL_HPP

#define BNS_OPENGL_UTIL_HPP


#include "util/OpenGLProgramUtil.hpp"
#include "util/bns_opengl_shader_util.hpp"
#include "util/OpenGLVAOUtil.hpp"
#include "util/bns_opengl_buffer_util.hpp"

namespace bns 
{

struct OpenGLUtil
{
    /// @brief The program util.
    static OpenGLProgramUtil Program;

    /// @brief The shader util.
    static OpenGLShaderUtil Shader;

    /// @brief The vertex array object util.
    static OpenGLVAOUtil VAO;

    /// @brief The buffer util.
    static OpenGLBufferUtil Buffer;
};

}

#endif // !BNS_OPENGL_UTIL_HPP

#endif // USE_OPENGL