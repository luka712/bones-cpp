#include "textures/TextureManagerImpl.hpp"
#include "Framework.hpp"

#if USE_METAL
#include "renderer/MetalRenderer.hpp"
#include "texture/MetalTexture2D.hpp"
#endif

#if USE_D3D11
#include "renderer/D3D11Renderer.hpp"
#include "texture/D3D11Texture2D.hpp"
#endif

#if USE_WEBGPU
#include "renderer/WebGPURenderer.hpp"
#include "texture/WebGPUTexture2D.hpp"
#endif

#if USE_OPENGL
#include "renderer/OpenGLRenderer.hpp"
#include "texture/OpenGLTexture2D.hpp"
#endif

namespace bns
{
	TextureManagerImpl::TextureManagerImpl(Renderer *renderer, ImageLoader *imageLoader)
		: TextureManager(imageLoader), m_renderer(renderer)
	{
	}

	Texture2D *TextureManagerImpl::CreateBackendImplTexture(ImageData *imageData, i32 textureUsageFlags, TextureFormat format)
	{
#if USE_METAL
		MetalRenderer *renderer = static_cast<MetalRenderer *>(m_renderer);
		return new MetalTexture2D(renderer->GetDevice(), imageData, textureUsageFlags, format);
#endif

#if USE_D3D11
		D3D11Renderer *renderer = static_cast<D3D11Renderer *>(m_renderer);
		return new D3D11Texture2D(renderer->GetDevice(), imageData, textureUsageFlags, format);
#endif

#if USE_WEBGPU
		WebGPURenderer *renderer = static_cast<WebGPURenderer *>(m_renderer);
		return new WebGPUTexture2D(renderer->GetDevice(), imageData, textureUsageFlags, format);
#endif

#if USE_OPENGL
		OpenGLRenderer *renderer = static_cast<OpenGLRenderer *>(m_renderer);
		return new OpenGLTexture2D(imageData, textureUsageFlags, format);
#endif

		// TODO: Implement OpenGL texture creation.
		throw std::runtime_error("Renderer not selected.");
		return nullptr;
	}
}
