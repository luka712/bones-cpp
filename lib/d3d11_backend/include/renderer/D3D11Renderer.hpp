#if USE_D3D11

#ifndef BNS_RENDERER_D3D11_HPP

#define BNS_RENDERER_D3D11_HPP

#include "BnsDirectX11.hpp"
#include "Window.hpp"
#include "bns_math.hpp"
#include "renderer/bns_renderer.hpp"

namespace bns
{
    class D3D11Renderer final : public Renderer
    {
    private:
        WindowManager *m_windowManager;

        /// @brief The device.
        CComPtr<ID3D11Device> m_device;

        /// @brief The device context.
        CComPtr<ID3D11DeviceContext> m_deviceContext;

        /// @brief The DXGI factory. It is responsible for creating DXGI objects. Creates the swap chain.
        CComPtr<IDXGIFactory2> m_dxgiFactory;

        /// @brief The swap chain. It is responsible for creating a swap chain.
        /// Swap chain in this context is a collection of buffers that can be drawn on.
        CComPtr<IDXGISwapChain1> m_swapChain;

        /// @brief The viewport.
        D3D11_VIEWPORT m_viewport;

        /// @brief A view into the back buffer texture that allows the GPU to render to it.
        CComPtr<ID3D11RenderTargetView> m_renderTargetView;

        /// @brief A depth stencil view is a view into a texture that allows the GPU to read and write depth information.
        CComPtr<ID3D11DepthStencilState> m_depthStencilState;

        /// @brief A texture that contains depth information for the scene.
        CComPtr<ID3D11Texture2D> m_depthStencilTexture;

        /// @brief A view into the depth stencil texture that allows the GPU to read and write depth information.
        CComPtr<ID3D11DepthStencilView> m_depthStencilView;

        /// @brief A rasterizer state object describes how triangles are rendered.
        CComPtr<ID3D11RasterizerState> m_rasterizerState;

        /// @brief Creates the device and device context.
        void CreateDeviceAndDeviceContext();

        /// @brief Creates the swap chain.
        void CreateSwapchain(HWND win32Handle);

        /// @brief Creates the depth stencil.
        /// @param width the width of the depth stencil.
        /// @param height the height of the depth stencil.
        void CreateDepthStencilBufferAndView(u32 width, u32 height);

        /// @brief Creates the rasterizer state. This is default rasterizer state.
        void CreateRasterizerState();

        /// @brief Resizes the swap chain.
        void Resize();

    public:
        D3D11Renderer(WindowManager *window);

        /// @brief Gets the renderer type.
        /// @return The renderer type.
        RendererType GetRendererType() const override { return RendererType::D3D11; }

        /// @brief Gets the device.
        /// @return The device.
        ID3D11Device *GetDevice() const { return m_device.p; }

        /// @brief Gets the device context.
        /// @return The device context.
        ID3D11DeviceContext *GetDeviceContext() const { return m_deviceContext.p; }

        /// @brief Gets the view into swap chain texture.
        void *GetSwapChainTexture() override;

        void Initialize(HWND win32Handle);
        void BeginDraw() override;
        void EndDraw() override;
        void Destroy() override;
    };
} // namespace BNS

#endif // !BNS_RENDERER_D3D11_HPP

#endif