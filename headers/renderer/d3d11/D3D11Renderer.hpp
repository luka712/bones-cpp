#ifndef BNS_RENDERER_D3D11_HPP

#define BNS_RENDERER_D3D11_HPP

#include "BNSDirectX.hpp"
#include "Math.hpp"
#include "renderer/Renderer.hpp"

namespace bns
{
    class Framework;

    class D3D11Renderer final : public Renderer
    {
    private:
        /// @brief The framework.
        Framework &m_framework;

        /// @brief The device.
        CComPtr<ID3D11Device> m_device;

        /// @brief The device context.
        CComPtr<ID3D11DeviceContext> m_deviceContext;
        
        /// @brief The swap chain. It is responsible for creating a swap chain.
        /// Swap chain in this context is a collection of buffers that can be drawn on.
        CComPtr<IDXGISwapChain> m_swapChain;
        
		/// @brief A view into the back buffer texture that allows the GPU to render to it.
		CComPtr<ID3D11RenderTargetView> m_renderTargetView;

		/// @brief A rasterizer state object describes how triangles are rendered.
		CComPtr<ID3D11RasterizerState> m_rasterizerState;

		/// @brief A depth stencil view is a view into a texture that allows the GPU to read and write depth information.
		CComPtr<ID3D11DepthStencilState> m_depthStencilState;

		/// @brief A texture that contains depth information for the scene.
		CComPtr<ID3D11Texture2D> m_depthStencilTexture;

		/// @brief A view into the depth stencil texture that allows the GPU to read and write depth information.
		CComPtr<ID3D11DepthStencilView> m_depthStencilView;

        /// @brief Configures the depth stencil.
        /// @param width the width of the depth stencil.
        /// @param height the height of the depth stencil.
        /// @return true if the depth stencil was configured successfully.
        bool ConfigureDepthStencil(u32 width, u32 height);

        /**
         * @brief Resizes the swap chain.
         */
        void Resize();

    public:
        D3D11Renderer(Framework &framework);


        /**
         * @brief Gets the view into swap chain texture.
         */
        void *GetSwapChainTexture() override;

        void Initialize(HWND win32Handle);
        void BeginDraw() override;
        void EndDraw() override;
        void Destroy() override;
    };
} // namespace BNS

#endif // !BNS_RENDERER_D3D11_HPP
