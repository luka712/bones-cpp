#include "renderer/bns_webgpu_renderer.hpp"
#include <iostream>
#include "texture/bns_webgpu_texture2d.hpp"
#include <assert.h>

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

	WGPUAdapter WebGPURenderer::CreateAdapter()
	{
		struct UserData
		{
			WGPUAdapter adapter = nullptr;
			bool isSuccess = false;
		} outData;

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
			UserData &userData = *reinterpret_cast<UserData *>(pUserData);
			if (status == WGPURequestAdapterStatus_Success)
			{
				userData.adapter = outAdapter;
				LOG("WebGPURenderer::CreateAdapter: WebGPU Adapter created.");
			}
			else
			{
				LOG("WebGPURenderer::CreateAdapter: Could not get WebGPU adapter: " << message);
			}
			userData.isSuccess = true;
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
			(void *)&outData);

		// In theory we should wait until onAdapterReady has been called, which
		// could take some time (what the 'await' keyword does in the JavaScript
		// code). In practice, we know that when the wgpuInstanceRequestAdapter()
		// function returns its callback has been called.
		assert(outData.isSuccess);
		
		m_adapter = outData.adapter;
		return m_adapter;
	}

	WGPUDevice WebGPURenderer::CreateDevice()
	{
		struct UserData
		{
			WGPUDevice device = nullptr;
			bool isSuccess = false;
		} userData;

		auto onDeviceRequestEnded = [](WGPURequestDeviceStatus status, WGPUDevice device, char const *message, void *pUserData)
		{
			UserData &userData = *reinterpret_cast<UserData *>(pUserData);
			if (status == WGPURequestDeviceStatus_Success)
			{
				userData.device = device;
				LOG("WebGPURenderer::CreateDevice: WebGPU Device created.");
			}
			else
			{
				LOG("WebGPURenderer::CreateDevice: Could not get WebGPU adapter: " << message);
				BREAKPOINT();
			}
			userData.isSuccess = true;
		};

		WGPUDeviceDescriptor deviceDescriptor = {};
		deviceDescriptor.nextInChain = nullptr;
		wgpuAdapterRequestDevice(
			m_adapter,
			&deviceDescriptor,
			onDeviceRequestEnded,
			(void *)&userData);

		assert(userData.isSuccess);

		m_device = userData.device;

		return userData.device;
	}

	void WebGPURenderer::Resize()
	{
		// The swap chaing is responsible for creating the buffers that can be drawn on.
		WGPUSwapChainDescriptor swapChainDesc;
		swapChainDesc.nextInChain = nullptr;
		swapChainDesc.format = WGPUTextureFormat_BGRA8Unorm;
		swapChainDesc.usage = WGPUTextureUsage_RenderAttachment;
		swapChainDesc.width = m_bufferSize.X;
		swapChainDesc.height = m_bufferSize.Y;
		swapChainDesc.presentMode = WGPUPresentMode_Mailbox;

		// Create the swap chain
		m_swapChain = wgpuDeviceCreateSwapChain(m_device, m_surface, &swapChainDesc);

		// TODO: depth texture
	}

	void WebGPURenderer::Initialize(WGPUInstance instance, WGPUSurface surface)
	{
		if (instance == nullptr)
		{
			std::cout << "WebGPU instance is null" << std::endl;
		}
		if (surface == nullptr)
		{
			std::cout << "WebGPU surface is null" << std::endl;
		}

		Vec2i windowSize = m_windowManager->GetWindowSize();
		m_bufferSize.X = windowSize.X;
		m_bufferSize.Y = windowSize.Y;

		m_instance = instance;
		m_surface = surface;

		m_adapter = CreateAdapter();
		m_device = CreateDevice();
		m_queue = wgpuDeviceGetQueue(m_device);

		auto onQueueDone = [](WGPUQueueWorkDoneStatus status, void *userData)
		{
			std::cout << "Queued work finished with status: " << status << std::endl;
		};
		wgpuQueueOnSubmittedWorkDone(m_queue, 0, onQueueDone, nullptr);

		auto handleWebGPUError = [](WGPUErrorType type, const char *message, void *userData)
		{
			// Handle the error here, such as logging or displaying an error message
			// You can access the error type and message to determine the cause of the error

			// Example: Printing the error message
			printf("WebGPU Error: %s\n", message);
		};

		// Set the error callback
		wgpuDeviceSetUncapturedErrorCallback(m_device, handleWebGPUError, nullptr);

		Resize(); // creates swap chain


		// move to create empty texture method
		ImageData imageData;
		imageData.Width = m_bufferSize.X;
		imageData.Height = m_bufferSize.Y;
		imageData.Data = new u8[m_bufferSize.X * m_bufferSize.Y * 4];
		TextureUsage textureUsage = TextureUsage::CopyDst_CopySrc_TextureBinding_RenderAttachment;
		TextureFormat format = TextureFormat::BGRA_8_Unorm;
		m_brightnessTexture = new WebGPUTexture2D(this, &imageData, textureUsage, format);
		m_brightnessTexture->Initialize();
	}

	void WebGPURenderer::BeginDraw()
	{
		wgpuDeviceTick(m_device);
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
} // namespace bns
