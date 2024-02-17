#include "textures/TextureManagerImpl.hpp"
#include "Framework.hpp"

#if USE_METAL
#include "renderer/Metalbns_renderer.hpp"
#include "texture/MetalTexture2D.hpp"
#endif

#if USE_VULKAN
#include "renderer/Vulkanbns_renderer.hpp"
#include "texture/VulkanTexture2D.hpp"
#endif

#if USE_D3D11
#include "renderer/D3D11bns_renderer.hpp"
#include "texture/D3D11Texture2D.hpp"
#endif

#if USE_WEBGPU
#include "renderer/bns_webgpu_renderer.hpp"
#include "texture/WebGPUTexture2D.hpp"
#endif

#if USE_OPENGL
#include "renderer/OpenGLbns_renderer.hpp"
#include "texture/OpenGLTexture2D.hpp"
#endif

#if USE_OPENGLES
#include "renderer/OpenGLESbns_renderer.hpp"
#include "texture/OpenGLESTexture2D.hpp"
#endif

namespace bns
{
	TextureManagerImpl::TextureManagerImpl(Renderer *renderer, ImageLoader *imageLoader)
		: TextureManager(imageLoader), m_renderer(renderer)
	{
	}

	Texture2D *TextureManagerImpl::CreateBackendImplTexture(ImageData *imageData, i32 textureUsageFlags, TextureFormat format,
															SamplerMinFilter samplerMinFilter, SamplerMagFilter samplerMagFilter)
	{
#if USE_METAL
		if (m_renderer->GetRendererType() == RendererType::Metal)
		{
			MetalRenderer *renderer = static_cast<MetalRenderer *>(m_renderer);
			return new MetalTexture2D(renderer->GetDevice(), imageData, textureUsageFlags, format);
		}
#endif

#if USE_VULKAN
		if (m_renderer->GetRendererType() == RendererType::Vulkan)
		{
			VulkanRenderer *renderer = static_cast<VulkanRenderer *>(m_renderer);

			return new VulkanTexture2D(
				renderer->GetPhysicalDevice(),
				renderer->GetDevice(),
				renderer->GetCommandPool(),
				renderer->GetGraphicsQueue(),
				imageData, textureUsageFlags, format, 
				samplerMinFilter, samplerMagFilter);
		}
#endif

#if USE_D3D11
		if(m_renderer->GetRendererType() == RendererType::D3D11)
		{
			D3D11Renderer *renderer = static_cast<D3D11Renderer *>(m_renderer);
			return new D3D11Texture2D(renderer->GetDevice(), imageData, textureUsageFlags, format, samplerMinFilter, samplerMagFilter);
		}
#endif

#if USE_WEBGPU
		if (m_renderer->GetRendererType() == RendererType::WebGPU)
		{
			WebGPURenderer *renderer = static_cast<WebGPURenderer *>(m_renderer);
			return new WebGPUTexture2D(renderer->GetDevice(), imageData, textureUsageFlags, format);
		}
#endif

#if USE_OPENGL
		OpenGLRenderer *renderer = static_cast<OpenGLRenderer *>(m_renderer);
		return new OpenGLTexture2D(imageData, textureUsageFlags, format, samplerMinFilter, samplerMagFilter);
#endif

#if USE_OPENGLES
		OpenGLESRenderer *renderer = static_cast<OpenGLESRenderer *>(m_renderer);
		return new OpenGLESTexture2D(imageData, textureUsageFlags, format, samplerMinFilter, samplerMagFilter);
#endif

		//
		throw std::runtime_error("Renderer not selected.");
		return nullptr;
	}
}
