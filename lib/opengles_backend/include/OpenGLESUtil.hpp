#if USE_OPENGLES

#ifndef BNS_OPENGLES_UTIL_HPP

#define BNS_OPENGLES_UTIL_HPP


#include "util/OpenGLESProgramUtil.hpp"
#include "util/OpenGLESShaderUtil.hpp"
#include "util/OpenGLESVAOUtil.hpp"
#include "util/OpenGLESBufferUtil.hpp"

namespace bns 
{

struct OpenGLESUtil
{
    /// @brief The program util.
    static OpenGLESProgramUtil Program;

    /// @brief The shader util.
    static OpenGLESShaderUtil Shader;

    /// @brief The vertex array object util.
    static OpenGLESVAOUtil VAO;

    /// @brief The buffer util.
    static OpenGLESBufferUtil Buffer;
};

}

#endif // !BNS_OPENGLES_UTIL_HPP

#endif // USE_OPENGLES