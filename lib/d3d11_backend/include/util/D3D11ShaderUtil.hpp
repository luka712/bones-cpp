#if USE_D3D11

#ifndef BNS_D3D11_SHADER_UTIL_HPP

#define BNS_D3D11_SHADER_UTIL_HPP

#include "BnsDirectX11.hpp"
#include <string>

namespace bns
{
    class D3D11ShaderUtil
    {
    public:
        /// @brief Creates a vertex shader from a blob.
        /// @param device The D3D11 device.
        /// @param blob The blob.
        /// @return The vertex shader.
        static CComPtr<ID3D11VertexShader> CreateVertexShader(CComPtr<ID3D11Device> device, CComPtr<ID3DBlob> blob);

        /// @brief Creates a pixel shader from a blob.
        /// @param device The D3D11 device.
        /// @param blob The blob.
        /// @return The pixel shader.
        static CComPtr<ID3D11PixelShader> CreatePixelShader(CComPtr<ID3D11Device> device, CComPtr<ID3DBlob> blob);
    };
}

#endif // !BNS_D3D11_SHADER_UTIL_HPP

#endif // USE_D3D11