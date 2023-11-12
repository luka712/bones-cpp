#if USE_D3D11

#ifndef BNS_D3D11_BLOB_UTIL_HPP

#define BNS_D3D11_BLOB_UTIL_HPP

#include "BnsDirectX11.hpp"
#include <string>

namespace bns
{
    class D3D11BlobUtil
    {
    public:
        /// @brief Loads and compiles shader from a file.
        /// @param fileName The filepath.
        /// @param d3d11ShaderModel The shader model. Usually "vs_5_0", "ps_5_0", "cs_5_0" etc.
        /// @param entryPoint The entry point.
        /// @return The compiled shader.
        static CComPtr<ID3DBlob> CompileFromFile(std::string filePath, std::string d3d11ShaderModel, std::string entryPoint);
    };
}

#endif // !BNS_D3D11_BLOB_UTIL_HPP

#endif // USE_D3D11