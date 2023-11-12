#if USE_D3D11

#include "util/D3D11ShaderUtil.hpp"
#include <exception>

namespace bns
{
    CComPtr<ID3D11VertexShader> D3D11ShaderUtil::CreateVertexShader(CComPtr<ID3D11Device> device, CComPtr<ID3DBlob> blob)
    {
        CComPtr<ID3D11VertexShader> vertexShader;
        HRESULT hr = device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &vertexShader);
        if (FAILED(hr))
        {
            throw std::exception("D3D11ShaderUtil::CreateVertexShader: Failed to create vertex shader.");
        }
        return vertexShader;
    }

    CComPtr<ID3D11PixelShader> D3D11ShaderUtil::CreatePixelShader(CComPtr<ID3D11Device> device, CComPtr<ID3DBlob> blob)
    {
        CComPtr<ID3D11PixelShader> pixelShader;
        HRESULT hr = device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &pixelShader);
        if (FAILED(hr))
        {
            throw std::exception("D3D11ShaderUtil::CreatePixelShader: Failed to create pixel shader.");
        }
        return pixelShader;
    }
}

#endif