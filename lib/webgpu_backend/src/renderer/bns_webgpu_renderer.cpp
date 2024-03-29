#include "renderer/bns_webgpu_renderer.hpp"
#include "texture/bns_webgpu_texture2d.hpp"
#include <stdexcept>

namespace bns
{

	WebGPURenderer::WebGPURenderer(WindowManager *windowManager)
		: Renderer(), m_windowManager(windowManager)
	{
	}

	void *WebGPURenderer::GetSwapChainTexture()
	{
		return wgpuSwapChainGetCurrentTexture(m_swapChain);
	}

	void WebGPURenderer::CreateAdapter()
	{
		// Callback called by wgpuInstanceRequestAdapter when the request returns
		// This is a C++ lambda function, but could be any function defined in the
		// global scope. It must be non-capturing (the brackets [] are empty) so
		// that it behaves like a regular C function pointer, which is what
		// wgpuInstanceRequestAdapter expects (WebGPU being a C API). The workaround
		// is to convey what we want to capture through the pUserData pointer,
		// provided as the last argument of wgpuInstanceRequestAdapter and received
		// by the callback as its last argument.
		auto onAdapterRequestEnded = [](WGPURequestAdapterStatus status, WGPUAdapter outAdapter, char const *message, void *pUserData)
		{
			if (status == WGPURequestAdapterStatus_Success)
			{
				LOG("WebGPURenderer::CreateAdapter: WebGPU Adapter created.");
			}
			else
			{
				std::string msg = "WebGPURenderer::CreateAdapter: Could not get WebGPU adapter: " + std::string(message);
				LOG(msg);
				BREAKPOINT();
				throw std::runtime_error(msg.c_str());
			}

			WGPUAdapter* wgpuAdapterPtr = static_cast<WGPUAdapter *>(pUserData);
			*wgpuAdapterPtr = outAdapter;
		};

		WGPURequestAdapterOptions options = {};

		WGPUDawnTogglesDescriptor togglesDesc;
		togglesDesc.chain.sType = WGPUSType_DawnTogglesDescriptor;
		const char *allowUnsafeApi = "allow_unsafe_apis";
		togglesDesc.enabledToggles = {&allowUnsafeApi};
		togglesDesc.enabledTogglesCount = 1;
		togglesDesc.disabledTogglesCount = 0;
		options.nextInChain = reinterpret_cast<WGPUChainedStruct *>(&togglesDesc);

		// Call to the WebGPU request adapter procedure
		wgpuInstanceRequestAdapter(
			m_instance /* equivalent of navigator.gpu */,
			&options,
			onAdapterRequestEnded,
			&m_adapter);
	}

	void WebGPURenderer::CreateDevice()
	{
		auto onDeviceRequestEnded = [](WGPURequestDeviceStatus status, WGPUDevice device, char const *message, void *ptrDevice)
		{
			if (status == WGPURequestDeviceStatus_Success)
			{
				LOG("WebGPURenderer::CreateDevice: WebGPU Device created.");
			}
			else
			{
				std::string msg = "WebGPURenderer::CreateDevice: Could not get WebGPU adapter: " + std::string(message);
				LOG(msg);
				BREAKPOINT();
				throw std::runtime_error(msg.c_str());
			}
			
			WGPUDevice* wgpuDevicePtr = static_cast<WGPUDevice *>(ptrDevice);
			*wgpuDevicePtr = device;
		};

		WGPUDeviceDescriptor deviceDescriptor = {};
		deviceDescriptor.nextInChain = nullptr;
		wgpuAdapterRequestDevice(m_adapter,	&deviceDescriptor,	onDeviceRequestEnded, &m_device);
	}

	void WebGPURenderer::SetupDebugCallback()
	{
		auto handleWebGPUError = [](WGPUErrorType type, const char *message, void *userData)
		{
			LOG("WebGPU Error: " << message);
		};

		// Set the error callback
		wgpuDeviceSetUncapturedErrorCallback(m_device, handleWebGPUError, nullptr);
	}

	void WebGPURenderer::Resize()
	{
		// The swap chain is responsible for creating the buffers that can be drawn on.
		WGPUSwapChainDescriptor swapChainDesc;
		swapChainDesc.nextInChain = nullptr;
        swapChainDesc.label = "Swapchain";
		swapChainDesc.format = WGPUTextureFormat_BGRA8Unorm;
		swapChainDesc.usage = WGPUTextureUsage_RenderAttachment;
		swapChainDesc.width = m_bufferSize.X;
		swapChainDesc.height = m_bufferSize.Y;
		swapChainDesc.presentMode = WGPUPresentMode_Fifo;

		// Create the swap chain
		m_swapChain = wgpuDeviceCreateSwapChain(m_device, m_surface, &swapChainDesc);

		// TODO: depth texture
        
        // Create second render attachment.
        m_brightnessTexture =  WebGPUTexture2D::CreateEmpty(this, m_bufferSize.X, m_bufferSize.Y, TextureUsage::CopyDst_CopySrc_TextureBinding_RenderAttachment);
        m_brightnessTexture->Initialize();
	}

	void WebGPURenderer::Initialize(WGPUInstance instance, WGPUSurface surface)
	{
		if (instance == nullptr)
		{
			std::string msg = "WebGPURenderer::Initialize: WebGPU instance is null";
			LOG(msg);
			BREAKPOINT();
			throw std::runtime_error(msg.c_str());
		}
		if (surface == nullptr)
		{
			std::string msg = "WebGPURenderer::Initialize: WebGPU surface is null";
			LOG(msg);
			BREAKPOINT();
			throw std::runtime_error(msg.c_str());
		}

		Vec2i windowSize = m_windowManager->GetWindowSize();
		m_bufferSize.X = windowSize.X;
		m_bufferSize.Y = windowSize.Y;

		m_instance = instance;
		m_surface = surface;

		CreateAdapter();
		CreateDevice();
		m_queue = wgpuDeviceGetQueue(m_device);
		SetupDebugCallback();
		Resize(); // creates swap chain

		// Listen to events
		std::function<void(Vec2i)> resizeCallback = [this](Vec2i size)
		{
			m_bufferSize = size;
			Resize();
		};
		m_windowManager->RegisterToWindowResize(resizeCallback);

		
	}

	void WebGPURenderer::HandleBlitCommands()
	{
		if (m_onBlitCommandEncoderAvailable.size() > 0)
		{
			m_blitCommandEncoder = wgpuDeviceCreateCommandEncoder(m_device, nullptr);
			// Blit commander is now available. Call methods that require blit command encoder and clear them.
			for (auto &callback : m_onBlitCommandEncoderAvailable)
			{
				callback(m_blitCommandEncoder);
			}
			m_onBlitCommandEncoderAvailable.clear();
			wgpuCommandEncoderFinish(m_blitCommandEncoder, nullptr);
		}
	}

	void WebGPURenderer::BeginDraw()
	{
		wgpuDeviceTick(m_device);

		HandleBlitCommands();

		m_drawCommandEncoder = wgpuDeviceCreateCommandEncoder(m_device, nullptr);

		WGPURenderPassColorAttachment colorAttachment[2];

		// if there is no render texture, we render to the swap chain
		if (m_renderTexture == nullptr)
		{
			m_currentTextureView = wgpuSwapChainGetCurrentTextureView(m_swapChain);
		}
		else
		{
			// if render texture is set, we render to it
			WGPUTexture wgpuTexture = static_cast<WebGPUTexture2D *>(m_renderTexture)->Texture;
			m_currentTextureView = wgpuTextureCreateView(wgpuTexture, nullptr);
		}
		colorAttachment[0].nextInChain = nullptr;
		colorAttachment[0].view = m_currentTextureView;
		colorAttachment[0].resolveTarget = nullptr;
		colorAttachment[0].clearValue = {ClearColor.R, ClearColor.G, ClearColor.B, ClearColor.A};
		colorAttachment[0].loadOp = WGPULoadOp_Clear;
		colorAttachment[0].storeOp = WGPUStoreOp_Store;

		WGPUTexture wgpuTexture = static_cast<WebGPUTexture2D *>(m_brightnessTexture)->Texture;
		m_brightnessTextureView = wgpuTextureCreateView(wgpuTexture, nullptr);

		colorAttachment[1].nextInChain = nullptr;
		colorAttachment[1].view = m_brightnessTextureView;
		colorAttachment[1].resolveTarget = nullptr;
		colorAttachment[1].clearValue = {ClearColor.R, ClearColor.G, ClearColor.B, ClearColor.A};
		colorAttachment[1].loadOp = WGPULoadOp_Clear;
		colorAttachment[1].storeOp = WGPUStoreOp_Store;

		WGPURenderPassDescriptor renderPassDesc = {};
		renderPassDesc.colorAttachmentCount = 2;
		renderPassDesc.colorAttachments = colorAttachment;
		renderPassDesc.depthStencilAttachment = nullptr;

		m_currentPassEncoder = wgpuCommandEncoderBeginRenderPass(m_drawCommandEncoder, &renderPassDesc);
		wgpuRenderPassEncoderPushDebugGroup(m_currentPassEncoder, "debug");

		// m_currentTextureView = wgpuSwapChainGetCurrentTextureView(m_swapChain);
		// WGPURenderPassDescriptor renderpassInfo = {};
		// WGPURenderPassColorAttachment colorAttachment = {};

		// colorAttachment.view = m_currentTextureView;
		// colorAttachment.resolveTarget = nullptr;
		// colorAttachment.clearValue = {ClearColor.R, ClearColor.G, ClearColor.B, ClearColor.A};
		// colorAttachment.loadOp = WGPULoadOp_Clear;
		// colorAttachment.storeOp = WGPUStoreOp_Store;
		// renderpassInfo.colorAttachmentCount = 1;
		// renderpassInfo.colorAttachments = &colorAttachment;
		// renderpassInfo.depthStencilAttachment = nullptr;

		// m_drawCommandEncoder = wgpuDeviceCreateCommandEncoder(m_device, nullptr);

		// m_currentPassEncoder = wgpuCommandEncoderBeginRenderPass(m_drawCommandEncoder, &renderpassInfo);
		// // wgpuRenderPassEncoderSetViewport(m_currentPassEncoder, 0.0f, 0.0f, m_bufferSize.X, m_bufferSize.Y, 0.0f, 1.0f);
		// //  wgpuRenderPassEncoderSetScissorRect(m_currentPassEncoder, 0, 0, m_bufferSize.X, m_bufferSize.Y);
	}

	void WebGPURenderer::EndDraw()
	{
		wgpuRenderPassEncoderPopDebugGroup(m_currentPassEncoder);

		if (m_blitCommandEncoder != nullptr)
		{
			wgpuCommandEncoderRelease(m_blitCommandEncoder);
			m_blitCommandEncoder = nullptr;
		}

		// End and release render pass encoder.
		wgpuRenderPassEncoderEnd(m_currentPassEncoder);
		wgpuRenderPassEncoderRelease(m_currentPassEncoder);

		WGPUCommandBuffer commands = wgpuCommandEncoderFinish(m_drawCommandEncoder, nullptr);
		wgpuCommandEncoderRelease(m_drawCommandEncoder);

		wgpuQueueSubmit(m_queue, 1, &commands);
		wgpuCommandBufferRelease(commands);

		// present to swap chain
		wgpuSwapChainPresent(m_swapChain);

		wgpuTextureViewRelease(m_currentTextureView);

		if (m_brightnessTextureView != nullptr)
		{
			wgpuTextureViewRelease(m_brightnessTextureView);
		}
	}

	void WebGPURenderer::Destroy()
	{
		wgpuSwapChainRelease(m_swapChain);
		wgpuDeviceRelease(m_device);
		wgpuAdapterRelease(m_adapter);
		wgpuInstanceRelease(m_instance);
	}

	void WebGPURenderer::OnBlitCommandEncoderAvailable(std::function<void(WGPUCommandEncoder)> callback)
	{
		m_onBlitCommandEncoderAvailable.push_back(callback);
	}
} // namespace bns
