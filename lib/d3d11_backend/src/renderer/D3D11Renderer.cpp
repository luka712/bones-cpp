#if USE_D3D11

#include "renderer/D3D11bns_renderer.hpp"
#include <stdexcept>

namespace bns
{
    D3D11Renderer::D3D11Renderer(WindowManager *window)
        : Renderer(), m_windowManager(window)
    {
    }

    void *D3D11Renderer::GetSwapChainTexture()
    {
        return m_renderTargetView.p;
    }

    void D3D11Renderer::Resize()
    {
    }

    void D3D11Renderer::CreateDeviceAndDeviceContext()
    {
        m_bufferSize = m_windowManager->GetWindowSize();

        // flags
        UINT createDeviceFlags = 0;
#if DEBUG
        createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

        D3D_FEATURE_LEVEL featureLevels = D3D_FEATURE_LEVEL_11_0;
        UINT featureLevelsCount = 1;
        D3D_FEATURE_LEVEL featureLevelSupported;

        HRESULT hr = D3D11CreateDevice(
            nullptr,                  // Use the default adapter
            D3D_DRIVER_TYPE_HARDWARE, // Use the hardware rendering driver
            nullptr,                  // No software device
            createDeviceFlags,        // Set debug and feature level
            &featureLevels,           // List of feature levels this app can support
            featureLevelsCount,       // Size of the list
            D3D11_SDK_VERSION,        // Always set this to D3D11_SDK_VERSION
            &m_device,                // Returns the Direct3D device created
            &featureLevelSupported,   // Returns feature level of device created
            &m_deviceContext);        // Returns the device immediate context

        if (FAILED(hr))
        {
            std::string msg = "D3D11::CreateDeviceAndDeviceContext: Failed to create device and device context";
            LOG(msg);
            BREAKPOINT();
            throw std::runtime_error(msg.c_str());
        }

        LOG("D3D11::CreateDeviceAndDeviceContext: D3D11 device and device context created successfully");
    }

    void D3D11Renderer::CreateSwapchain(HWND win32Handle)
    {
        // we need to get the DXGI device
        CComPtr<IDXGIDevice> dxgiDevice;
        HRESULT hr = m_device->QueryInterface(__uuidof(IDXGIDevice), (void **)&dxgiDevice);
        if (FAILED(hr))
        {
            std::string msg = "D3D11::CreateSwapchain: Failed to query interface for IDXGIDevice";
            LOG(msg);
            BREAKPOINT();
            throw std::runtime_error(msg.c_str());
        }
        LOG("D3D11::CreateSwapchain: Got the DXGI device");

        // we need to get the DXGI adapter
        CComPtr<IDXGIAdapter> dxgiAdapter;
        hr = dxgiDevice->GetAdapter(&dxgiAdapter);
        if (FAILED(hr))
        {
            std::string msg = "D3D11::CreateSwapchain: Failed to get adapter";
            LOG(msg);
            BREAKPOINT();
            throw std::runtime_error(msg.c_str());
        }
        LOG("D3D11::CreateSwapchain: Got the DXGI adapter");

        // we need to get the DXGI factory
        hr = dxgiAdapter->GetParent(__uuidof(IDXGIFactory2), (void **)&m_dxgiFactory);
        if (FAILED(hr))
        {
            std::string msg = "D3D11::CreateSwapchain: Failed to get parent";
            LOG(msg);
            BREAKPOINT();
            throw std::runtime_error(msg.c_str());
        }
        LOG("D3D11::CreateSwapchain: Got the DXGI factory");

        // By default we use double buffering
        UINT numberOfPresentationBuffers = 2;
        if (m_presentationMode == SurfacePresentationMode::TripleBuffering)
        {
            numberOfPresentationBuffers = 3;
        }
        else if (m_presentationMode == SurfacePresentationMode::SingleBuffer)
        {
            numberOfPresentationBuffers = 1;
        }

        DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
        ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC1));
        swapChainDesc.Width = m_bufferSize.X;
        swapChainDesc.Height = m_bufferSize.Y;
        swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        swapChainDesc.Stereo = FALSE;
        swapChainDesc.SampleDesc.Count = 1;
        swapChainDesc.SampleDesc.Quality = 0;
        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.BufferCount = numberOfPresentationBuffers;
        swapChainDesc.Scaling = DXGI_SCALING_STRETCH; // stretch the back buffer to fit the entire window, even it's smaller.
        swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
        swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_IGNORE;
        swapChainDesc.Flags = 0;

        hr = m_dxgiFactory->CreateSwapChainForHwnd(
            m_device,       // The device
            win32Handle,    // The window
            &swapChainDesc, // Swap chain description
            nullptr,        // Full screen description
            nullptr,        // Restrict output
            &m_swapChain);  // The swap chain

        if (FAILED(hr))
        {
            std::string msg = "D3D11::CreateSwapchain: Failed to create swap chain";
            LOG(msg);
            BREAKPOINT();
            throw std::runtime_error(msg.c_str());
        }
        LOG("D3D11::CreateSwapchain: Swap chain created successfully");


        // RELEASE
        dxgiDevice.Release();
        dxgiAdapter.Release();
    }

    void D3D11Renderer::CreateDepthStencilBufferAndView(u32 Width, u32 Height)
    {
        m_depthStencilTexture = nullptr;

        D3D11_TEXTURE2D_DESC descDepth;
        descDepth.Width = Width;
        descDepth.Height = Height;
        descDepth.MipLevels = 1;
        descDepth.ArraySize = 1;
        descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        descDepth.SampleDesc.Count = 1;
        descDepth.SampleDesc.Quality = 0;
        descDepth.Usage = D3D11_USAGE_DEFAULT;
        descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
        descDepth.CPUAccessFlags = 0;
        descDepth.MiscFlags = 0;

        // create a buffer(texture) for the depth stencil
        HRESULT hr = m_device->CreateTexture2D(&descDepth, nullptr, &m_depthStencilTexture.p);
        if (FAILED(hr))
        {
            std::string msg = "D3D11::CreateDepthStencilBuffer: Failed to create depth stencil buffer.";
            LOG(msg);
            BREAKPOINT();
            throw std::runtime_error(msg.c_str());
        }
        LOG("D3D11::CreateDepthStencilBuffer: Depth stencil buffer created successfully.");

        // Create the depth stencil view
        hr = m_device->CreateDepthStencilView(m_depthStencilTexture, nullptr, &m_depthStencilView.p);
        if (FAILED(hr))
        {
            std::string msg = "D3D11::CreateDepthStencilBuffer: Failed to create depth stencil view.";
            LOG(msg);
            BREAKPOINT();
            throw std::runtime_error(msg.c_str());
        }
        LOG("D3D11::CreateDepthStencilBuffer: Depth stencil view created successfully.");
    }

    void D3D11Renderer::CreateRasterizerState()
    {
        D3D11_RASTERIZER_DESC raster_desc;
        raster_desc.FillMode = D3D11_FILL_SOLID;
        raster_desc.CullMode = D3D11_CULL_FRONT;
        raster_desc.FrontCounterClockwise = true;
        raster_desc.DepthBias = 0;
        raster_desc.DepthBiasClamp = 0.0f;
        raster_desc.SlopeScaledDepthBias = 0.0f;
        raster_desc.DepthClipEnable = true;
        raster_desc.ScissorEnable = false;
        raster_desc.MultisampleEnable = false;
        raster_desc.AntialiasedLineEnable = false;

        HRESULT hr = m_device->CreateRasterizerState(&raster_desc, &m_rasterizerState.p);
        if (FAILED(hr))
        {
            std::string msg = "D3D11::CreateRasterizerState: Failed to create rasterizer state.";
            LOG(msg);
            BREAKPOINT();
            throw std::runtime_error(msg.c_str());
        }
        LOG("D3D11::CreateRasterizerState: Rasterizer state created successfully.");
    }

    void D3D11Renderer::Initialize(HWND win32Handle)
    {
        CreateDeviceAndDeviceContext();
        CreateSwapchain(win32Handle);

        m_bufferSize = m_windowManager->GetWindowSize();

        CreateDepthStencilBufferAndView(m_bufferSize.X, m_bufferSize.Y);

        // Create the viewport
        m_viewport = CD3D11_VIEWPORT(
            0.0f,
            0.0f,
            static_cast<float>(m_bufferSize.X),
            static_cast<float>(m_bufferSize.Y));       

        CreateRasterizerState();
    }

    void D3D11Renderer::BeginDraw()
    {
        // Get a pointer to the back buffer.
        CComPtr<ID3D11Texture2D> framebuffer;
        HRESULT hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void **>(&framebuffer.p));
        if (FAILED(hr))
        {
            std::string msg = "D3D11::BeginDraw: Failed to get back buffer.";
            LOG(msg);
            BREAKPOINT();
            throw std::runtime_error(msg.c_str());
        }

        // Create a render target view
        hr = m_device->CreateRenderTargetView(framebuffer, nullptr, &m_renderTargetView.p);
        if (FAILED(hr))
        {
            std::string msg = "D3D11::BeginDraw: Failed to create render target view.";
            LOG(msg);
            BREAKPOINT();
            throw std::runtime_error(msg.c_str());
        }

        // CLEAR COLOR
        m_deviceContext->ClearRenderTargetView(m_renderTargetView, &ClearColor.R);

        // CLEAR DEPTH STENCIL
        m_deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

        // VIEWPORT
        m_deviceContext->RSSetViewports(1, &m_viewport);

        // DRAW TO SCREEN TEXTURE
        ID3D11RenderTargetView *renderTargetViewPtr = m_renderTargetView.p;
        ID3D11DepthStencilView *depthStencilViewPtr = m_depthStencilView.p;
        m_deviceContext->OMSetRenderTargets(1, &renderTargetViewPtr, depthStencilViewPtr);

        // DEFAULT RASTER STATE
        m_deviceContext->RSSetState(m_rasterizerState);

        // RELEASE
        framebuffer.Release();
    }

    void D3D11Renderer::EndDraw()
    {
        // PRESENT
        // arg0: 1 for VSYNC, 0 for no VSYNC
        // arg1: flags. 0 for default
        m_swapChain->Present(1, 0);

        // RELEASE
        m_renderTargetView.Release();
    }

    void D3D11Renderer::Destroy()
    {
        m_rasterizerState.Release();
		m_depthStencilView.Release();
		m_depthStencilTexture.Release();
		m_swapChain.Release();
		m_deviceContext.Release();
		m_device.Release();
    }
}

#endif