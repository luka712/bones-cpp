#include "Framework.hpp"
#include <vector>
#if USE_METAL
#include "renderer/MetalRenderer.hpp"
#endif
#if USE_WEBGPU
#include "renderer/WebGPURenderer.hpp"
#endif
#if USE_D3D11
#include "renderer/D3D11Renderer.hpp"
#include "sprite/D3D11UnlitSpriteRenderer.hpp"
#endif
#if USE_OPENGL
#include "renderer/OpenGLRenderer.hpp"
#include "sprite/OpenGLUnlitSpriteRenderer.hpp"
#endif
#if USE_OPENGLES
#include "renderer/OpenGLESRenderer.hpp"
#include "sprite/OpenGLESUnlitSpriteRenderer.hpp"
#endif

#include "SDLWindow.hpp"
#include "material/WebGPUMaterialFactory.hpp"
#include "mesh/wgpu/WebGPUMeshFactory.hpp"
#include "mesh/metal/MetalMeshFactory.hpp"
#include "renderer/common/WebGPURenderPipelineUtil.hpp"
#include "camera/FreeCamera.hpp"
#include "material/test/wgpu/WebGPUNoMeshTestMaterial.hpp"
#include "material/test/wgpu/WebGPUBasicMeshTexturedTestMaterial.hpp"
#include "material/test/metal/MetalNoMeshTestMaterial.hpp"
#include "material/test/metal/MetalBasicMeshTestMaterial.hpp"
#include "material/test/metal/MetalBasicMeshTexturedTestMaterial.hpp"
#include "texture/MetalTexture2D.hpp"
#include "sprite/wgpu/WebGPUSpriteRenderer.hpp"
#include "sprite/metal/MetalSpriteRenderer.hpp"
#include "textures/TextureManagerImpl.hpp"

namespace bns
{
    Framework::Framework()
    {
        m_geometryBuilder = new GeometryBuilder();
        m_imageLoader = new ImageLoader();
        m_bitmapSpriteFontLoader = new BitmapSpriteFontLoader(*this);

        m_effectFactory = new EffectFactory(*this);
        m_windowManager = new SDLWindowManager();

#if USE_METAL
        m_renderer = new MetalRenderer(m_windowManager);
        // m_materialFactory = new MetalMaterialFactory(*this);
        m_meshFactory = new MetalMeshFactory(*this);
        m_spriteRenderer = new MetalSpriteRenderer(*this, *m_renderer);
#elif USE_D3D11
        m_renderer = new D3D11Renderer(m_windowManager);
        // m_materialFactory = new D3D11MaterialFactory(*this);
        // m_meshFactory = new D3D11MeshFactory(*this);
        m_spriteRenderer = new D3D11UnlitSpriteRenderer(m_renderer);
#elif USE_WEBGPU
        m_renderer = new WebGPURenderer(m_windowManager);
        m_materialFactory = new WebGPUMaterialFactory(*this);
        m_meshFactory = new WebGPUMeshFactory(*this);
        m_spriteRenderer = new WebGPUSpriteRenderer(m_renderer);
#elif USE_OPENGL
        m_renderer = new OpenGLRenderer(m_windowManager);
        // m_materialFactory = new OpenGLMaterialFactory(*this);
        // m_meshFactory = new OpenGLMeshFactory(*this);
        m_spriteRenderer = new OpenGLUnlitSpriteRenderer(m_renderer);
#elif USE_OPENGLES
        m_renderer = new OpenGLESRenderer(m_windowManager);
        // m_materialFactory = new OpenGLESMaterialFactory(*this);
        // m_meshFactory = new OpenGLESMeshFactory(*this);
        m_spriteRenderer = new OpenGLESUnlitSpriteRenderer(m_renderer);
#endif
        m_textureFactory = new TextureManagerImpl(m_renderer, m_imageLoader);
    }

    Framework::~Framework()
    {
    }

    void Framework::Initialize(WindowParameters windowParameters, std::function<void()> callback)
    {
#if USE_METAL
        InitializeForMetal(windowParameters);
#elif USE_D3D11
        InitializeForD3D11(windowParameters);
#elif USE_WEBGPU
        InitializeForWGPU(windowParameters);
#elif USE_OPENGL
        InitializeForOpenGL(windowParameters);
#elif USE_OPENGLES
        InitializeForOpenGLES(windowParameters);
#endif
        m_spriteRenderer->Initialize();

        callback();
    }

#if USE_WEBGPU
    void Framework::InitializeForWGPU(WindowParameters windowParameters)
    {
        WGPUInstance instance;
        WGPUSurface surface;
        m_windowManager->InitializeForWGPU(windowParameters, &instance, &surface);

        WebGPURenderer *webGPURenderer = static_cast<WebGPURenderer *>(m_renderer);
        webGPURenderer->Initialize(instance, surface);
    }
#endif // USE_WEBGPU

#if USE_METAL
    void Framework::InitializeForMetal(WindowParameters windowParameters)
    {
        CA::MetalLayer *swapchain = m_windowManager->InitializeForMetal(windowParameters);
        static_cast<MetalRenderer *>(m_renderer)->Initialize(swapchain);
    }
#endif // __APPLE__

#if USE_D3D11
    void Framework::InitializeForD3D11(WindowParameters windowParameters)
    {
        HWND hwnd = m_windowManager->InitializeForD3D11(windowParameters);
        static_cast<D3D11Renderer *>(m_renderer)->Initialize(hwnd);
    }
#endif // WIN32

#if USE_OPENGL
    void Framework::InitializeForOpenGL(WindowParameters windowParameters)
    {
        m_windowManager->InitializeForOpenGL(windowParameters);
        static_cast<OpenGLRenderer *>(m_renderer)->Initialize();
    }
#endif

#if USE_OPENGLES
    void Framework::InitializeForOpenGLES(WindowParameters windowParameters)
    {
        m_windowManager->InitializeForOpenGLES(windowParameters);
        static_cast<OpenGLESRenderer *>(m_renderer)->Initialize();
    }
#endif

    void Framework::Draw(std::function<void()> callback)
    {
        bool quit = false;
        SDL_Event event;

        while (!quit)
        {
            // Process events
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    quit = true;
                }
            }

            // #if __USE_WEBGPU__
            // Do nothing, this checks for ongoing asynchronous operations and call their callbacks
            // NOTE: this is specific to DAWN and is not part of WebGPU standard.
            // TODO: move to renderer of webgpu
            // #endif

            m_renderer->BeginDraw();
            m_spriteRenderer->BeginFrame();

            callback();

            m_spriteRenderer->EndFrame();
            m_renderer->EndDraw();

            SDL_Delay(16);
        }
    }
} // namespace BNS
