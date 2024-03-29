#include "bns_framework.hpp"
#include <vector>
#if USE_METAL
#include "renderer/bns_metal_renderer.hpp"
#include "sprite/bns_metal_unlit_sprite_renderer.hpp"
#endif
#if USE_WEBGPU
#include "renderer/bns_webgpu_renderer.hpp"
#include "sprite/bns_webgpu_unlit_sprite_renderer.hpp"
#endif
#if USE_D3D11
#include "renderer/D3D11bns_renderer.hpp"
#include "sprite/D3D11Unlitbns_sprite_renderer.hpp"
#endif
#if USE_OPENGL
#include "renderer/bns_opengl_renderer.hpp"
// for apple machine use 400 version, since 450 is not available/supported
#if __APPLE__
#include "sprite/400/OpenGL400Unlitbns_sprite_renderer.hpp"
#else
#include "sprite/OpenGLUnlitSpriteRenderer.hpp"
#endif
#endif // USE_OPENGL
#if USE_OPENGLES
#include "renderer/OpenGLESbns_renderer.hpp"
#include "sprite/OpenGLESUnlitbns_sprite_renderer.hpp"
#endif
#if USE_VULKAN
#include "renderer/Vulkanbns_renderer.hpp"
#include "sprite/VulkanUnlitbns_sprite_renderer.hpp"
#endif

#include "SDLWindow.hpp"
#include "material/WebGPUMaterialFactory.hpp"
#include "mesh/wgpu/WebGPUMeshFactory.hpp"
#include "mesh/metal/MetalMeshFactory.hpp"
#include "camera/FreeCamera.hpp"
#include "material/test/wgpu/WebGPUNoMeshTestMaterial.hpp"
#include "material/test/wgpu/WebGPUBasicMeshTexturedTestMaterial.hpp"
#include "material/test/metal/MetalNoMeshTestMaterial.hpp"
#include "material/test/metal/MetalBasicMeshTestMaterial.hpp"
#include "material/test/metal/MetalBasicMeshTexturedTestMaterial.hpp"
#include "texture/bns_metal_texture2d.hpp"
#include "sprite/wgpu/bns_webgpu_sprite_renderer.hpp"
#include "time/SDLTimeManager.hpp"

#include "textures/TextureManagerImpl.hpp"

namespace bns
{
	FrameworkDescription::FrameworkDescription()
	{
		RendererType = RendererType::None;
	}

	Framework::Framework(FrameworkDescription desc)
	{
		m_lifecycleState = LifecycleState::Created;
		UpdateCallback = [](Time) {};
		DrawCallback = []() {};
		m_currentRendererType = desc.RendererType;

		m_events = new Events();
		m_timeManager = new SDLTimeManager(120.0f);
		m_geometryBuilder = new GeometryBuilder();
		m_imageLoader = new ImageLoader();
		m_bitmapSpriteFontLoader = new BitmapSpriteFontLoader(*this);
		m_cameraFactory = new CameraFactory(this);
		m_effectFactory = new EffectFactory(*this);
		m_windowManager = new SDLWindowManager(m_events, m_timeManager,
			[=](Time time) { UpdateCallback(time); },
			std::bind(&Framework::OnDraw, this));

		CreateRenderObjects();
        
        // Depends on render object.
        m_bufferFactory = new BufferFactory(this->m_renderer);
		m_pipelineFactory = new PipelineFactory(this->m_renderer);
	}

	void Framework::CreateRenderObjects()
	{
		if (m_currentRendererType == RendererType::None)
		{
			// if apple machine and metal is available use metal
#if USE_METAL
			m_currentRendererType = RendererType::Metal;
#elif USE_D3D11
			m_currentRendererType = RendererType::D3D11;
			// MULTIPLATFORM HERE
#elif USE_VULKAN
			m_currentRendererType = RendererType::Vulkan;
#elif USE_OPENGL
			m_currentRendererType = RendererType::OpenGL;
#elif USE_WEBGPU
			m_currentRendererType = RendererType::WebGPU;
#elif USE_OPENGLES
			m_currentRendererType = RendererType::OpenGLES;
#endif
		}

#if USE_METAL
		if (m_currentRendererType == RendererType::Metal)
		{
			m_renderer = new MetalRenderer(m_windowManager);
			// m_materialFactory = new MetalMaterialFactory(*this);
			m_meshFactory = new MetalMeshFactory(*this);
			m_spriteRenderer = new MetalUnlitSpriteRenderer(m_renderer);
		}
#endif

#if USE_D3D11
		if (m_currentRendererType == RendererType::D3D11)
		{
			m_renderer = new D3D11Renderer(m_windowManager);
			// m_materialFactory = new D3D11MaterialFactory(*this);
			// m_meshFactory = new D3D11MeshFactory(*this);
			m_spriteRenderer = new D3D11UnlitSpriteRenderer(m_renderer);
		}
#endif

#if USE_WEBGPU
		if (m_currentRendererType == RendererType::WebGPU)
		{
			m_renderer = new WebGPURenderer(m_windowManager);
			m_materialFactory = new WebGPUMaterialFactory(*this);
			m_meshFactory = new WebGPUMeshFactory(*this);
			m_spriteRenderer = new WebGPUUnlitSpriteRenderer(m_renderer);
		}
#endif
#if USE_OPENGL
		if (m_currentRendererType == RendererType::OpenGL)
		{
			m_renderer = new OpenGLRenderer(m_windowManager);
			// m_materialFactory = new OpenGLMaterialFactory(*this);
			// m_meshFactory = new OpenGLMeshFactory(*this);

#if __APPLE__
			m_spriteRenderer = new OpenGL400UnlitSpriteRenderer(m_renderer);
#else
			m_spriteRenderer = new OpenGLUnlitSpriteRenderer(m_renderer);
#endif // __APPLE__
		}
#endif

#if USE_OPENGLES
		if (m_currentRendererType == RendererType::OpenGLES)
		{
			m_renderer = new OpenGLESRenderer(m_windowManager);
			// m_materialFactory = new OpenGLESMaterialFactory(*this);
			// m_meshFactory = new OpenGLESMeshFactory(*this);
			m_spriteRenderer = new OpenGLESUnlitSpriteRenderer(m_renderer);
		}
#endif

#if USE_VULKAN
		if (m_currentRendererType == RendererType::Vulkan)
		{
			m_renderer = new VulkanRenderer(m_windowManager);
			m_spriteRenderer = new VulkanUnlitSpriteRenderer(m_renderer);
		}
#endif

		m_textureFactory = new TextureManagerImpl(m_renderer, m_imageLoader);
	}

	void Framework::DestroyRenderObjects()
	{
		// TODO:
		// m_textureFactory->Destroy();
		// m_spriteRenderer->Destroy();
		// m_meshFactory->Destroy();
		// m_materialFactory->Destroy();
		m_renderer->Destroy();

		// TODO:
		// delete m_textureFactory;
		// delete m_spriteRenderer;
		//  delete m_meshFactory;
		//  delete m_materialFactory;
		// delete m_renderer;

		m_windowManager->Destroy();
	}

	Framework::~Framework()
	{
		DestroyRenderObjects();
	}

	void Framework::Initialize(WindowParameters windowParameters, std::function<void()> callback)
	{
		m_windowParameters = windowParameters;
		m_initializeCallback = callback;

#if USE_METAL
		if (m_currentRendererType == RendererType::Metal)
			InitializeForMetal(windowParameters);
#endif
#if USE_D3D11
		if (m_currentRendererType == RendererType::D3D11)
			InitializeForD3D11(windowParameters);
#endif
#if USE_OPENGL
		if (m_currentRendererType == RendererType::OpenGL)
			InitializeForOpenGL(windowParameters);
#endif
#if USE_OPENGLES
		if (m_currentRendererType == RendererType::OpenGLES)
			InitializeForOpenGLES(windowParameters);
#endif
#if USE_WEBGPU
		if (m_currentRendererType == RendererType::WebGPU)
			InitializeForWGPU(windowParameters);
#endif
#if USE_VULKAN 
		if (m_currentRendererType == RendererType::Vulkan)
			InitializeForVulkan(windowParameters);
#endif 
		m_spriteRenderer->Initialize();

		m_initializeCallback();

		if (m_lifecycleState == LifecycleState::Created)
		{
			// Loop only needs to be run once
			m_windowManager->RunEventLoop();
			m_lifecycleState = LifecycleState::Initialized;
		}
	}

#if USE_WEBGPU
	void Framework::InitializeForWGPU(WindowParameters windowParameters)
	{
		WGPUInstance instance;
		WGPUSurface surface;
		m_windowManager->InitializeForWGPU(windowParameters, &instance, &surface);

		WebGPURenderer* webGPURenderer = static_cast<WebGPURenderer*>(m_renderer);
		webGPURenderer->Initialize(instance, surface);
	}
#endif // USE_WEBGPU

#if USE_METAL
	void Framework::InitializeForMetal(WindowParameters windowParameters)
	{
		CA::MetalLayer* swapchain = m_windowManager->InitializeForMetal(windowParameters);
		static_cast<MetalRenderer*>(m_renderer)->Initialize(swapchain);
	}
#endif // __APPLE__

#if USE_D3D11
	void Framework::InitializeForD3D11(WindowParameters windowParameters)
	{
		HWND hwnd = m_windowManager->InitializeForD3D11(windowParameters);
		static_cast<D3D11Renderer*>(m_renderer)->Initialize(hwnd);
	}
#endif // WIN32

#if USE_OPENGL
	void Framework::InitializeForOpenGL(WindowParameters windowParameters)
	{
		static_cast<OpenGLRenderer*>(m_renderer)->Initialize();
	}
#endif

#if USE_OPENGLES
	void Framework::InitializeForOpenGLES(WindowParameters windowParameters)
	{
		static_cast<OpenGLESRenderer*>(m_renderer)->Initialize();
	}
#endif

#if USE_VULKAN
	void Framework::InitializeForVulkan(WindowParameters windowParameters)
	{
		std::vector<std::string> requiredExtensions;
		m_windowManager->InitializeForVulkan(windowParameters, &requiredExtensions);
		static_cast<VulkanRenderer*>(m_renderer)->Initialize(requiredExtensions);
	}
#endif

	void Framework::OnDraw()
	{
		m_renderer->BeginDraw();
		m_spriteRenderer->BeginFrame();

		DrawCallback();

		m_spriteRenderer->EndFrame();
		m_renderer->EndDraw();
	}

	void Framework::SwitchRenderer(RendererType rendererType)
	{
		if (m_currentRendererType == rendererType)
		{
			return;
		}

		m_currentRendererType = rendererType;

		DestroyRenderObjects();
		CreateRenderObjects();
		Initialize(m_windowParameters, m_initializeCallback);
	}

	void Framework::Destroy()
	{
		m_lifecycleState = LifecycleState::Destroyed;
		DestroyRenderObjects();
		delete m_events;
		delete m_timeManager;
		delete m_geometryBuilder;
		delete m_imageLoader;
		delete m_bitmapSpriteFontLoader;
		delete m_effectFactory;
		delete m_windowManager;
		delete m_bufferFactory;
		delete m_cameraFactory;
	}
} // namespace BNS
