#if USE_D3D11

#ifndef BNS_D3D11_UTIL_HPP

#define BNS_D3D11_UTIL_HPP

#include "util/D3D11BufferUtil.hpp"
#include "util/D3D11BlobUtil.hpp"
#include "util/D3D11ShaderUtil.hpp"
#include "util/D3D11BlendStateUtil.hpp"

namespace bns
{
    struct D3D11Util final
    {
        /// @brief The blend state util.
        static D3D11BlendStateUtil BlendState;

        /// @brief The buffer util.
        static D3D11BufferUtil Buffer;

        /// @brief The blob util. Used for compiling shaders.
        static D3D11BlobUtil Blob;

        /// @brief The shader util.
        static D3D11ShaderUtil Shader;
    };
}

#endif // BNS_D3D11_UTIL_HPP

#endif // USE_D3D11