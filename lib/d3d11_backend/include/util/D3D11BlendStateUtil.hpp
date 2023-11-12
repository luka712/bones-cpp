#if USE_D3D11

#ifndef BNS_D3D11_BLENDSTATE_UTIL_HPP

#define BNS_D3D11_BLENDSTATE_UTIL_HPP

#include "BnsDirectX11.hpp"

namespace bns
{
    class D3D11BlendStateUtil
    {
    public:
   
        /// @brief Creates the default blend state.
        /// @param device The D3D11 device.
        /// @return The blend state. By default set to alpha blending.
        static CComPtr<ID3D11BlendState> Create(CComPtr<ID3D11Device> device);
    };
}

#endif // !BNS_D3D11_BLENDSTATE_UTIL_HPP

#endif // USE_D3D11