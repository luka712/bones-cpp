#if USE_D3D11

#include "util/D3D11BlendStateUtil.hpp"
#include <exception>

namespace bns
{
    CComPtr<ID3D11BlendState> D3D11BlendStateUtil::Create(CComPtr<ID3D11Device> device)
    {
        D3D11_BLEND_DESC blendDesc;
        ZeroMemory(&blendDesc, sizeof(blendDesc));

        blendDesc.RenderTarget[0].BlendEnable = TRUE;
        blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
        blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
        blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
        blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
        blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
        blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
        blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

        CComPtr<ID3D11BlendState> blendState;
        HRESULT hr = device->CreateBlendState(&blendDesc, &blendState.p);

        if (FAILED(hr))
        {
            throw std::exception("D3D11BlendStateUtil::Create: Failed to create blend state");
        }

        return blendState;
    }
}

#endif