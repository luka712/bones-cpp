#if USE_D3D11

#include "sprite/D3D11UnlitSpritePipeline.hpp"
#include "D3D11Util.hpp"

namespace bns
{
    D3D11UnlitSpritePipeline::D3D11UnlitSpritePipeline(
        CComPtr<ID3D11VertexShader> vertexShader,
        CComPtr<ID3D11PixelShader> pixelShader,
        CComPtr<ID3D11InputLayout> inputLayout,
         CComPtr<ID3D11BlendState> blendState,
        D3D11Texture2D *texture)
        : m_vertexShader(vertexShader), m_pixelShader(pixelShader), m_inputLayout(inputLayout), m_blendState(blendState), m_texture(texture)
    {
        InstanceIndex = 0;
    }

    D3D11UnlitSpritePipeline::~D3D11UnlitSpritePipeline()
    {
        Release();
    }

    D3D11UnlitSpritePipeline *D3D11UnlitSpritePipeline::Create(CComPtr<ID3D11Device> device, D3D11Texture2D *texture)
    {
        // Compile the vertex shader from a file
        CComPtr<ID3DBlob> vertexShaderBlob = D3D11Util::Blob.CompileFromFile("./shaders/d3d11/sprite/unlit_sprite_vs.hlsl", "vs_5_0", "main");

        // Compile the pixel shader from a file
        CComPtr<ID3DBlob> pixelShaderBlob = D3D11Util::Blob.CompileFromFile("./shaders/d3d11/sprite/unlit_sprite_ps.hlsl", "ps_5_0", "main");

        CComPtr<ID3D11VertexShader> vertexShader = D3D11Util::Shader.CreateVertexShader(device, vertexShaderBlob);
        CComPtr<ID3D11PixelShader> pixelShader = D3D11Util::Shader.CreatePixelShader(device, pixelShaderBlob);

        // TODO: move input layout to util
        D3D11_INPUT_ELEMENT_DESC layout[] = {
            {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0}};

        CComPtr<ID3D11InputLayout> inputLayout;

        // Create the input layout
        HRESULT hr = device->CreateInputLayout(
            layout,
            3,
            vertexShaderBlob->GetBufferPointer(),
            vertexShaderBlob->GetBufferSize(),
            &inputLayout);

        if (FAILED(hr))
        {
            throw std::exception("D3D11UnlitSpritePipeline::Create: Failed to create input layout.");
        }

        // BLENDSTATE
        CComPtr<ID3D11BlendState> blendState = D3D11Util::BlendState.Create(device);

        return new D3D11UnlitSpritePipeline(vertexShader, pixelShader, inputLayout, blendState, texture);
    }

    void D3D11UnlitSpritePipeline::Release()
    {
        m_vertexShader.Release();
        m_pixelShader.Release();
        m_inputLayout.Release();
    }
}

#endif