#include "Framework.hpp"
#include <vector>
#include "renderer/metal/MetalRenderer.hpp"
#include "renderer/wgpu/WebGPURenderer.hpp"
#include "renderer/d3d11/D3D11Renderer.hpp"
#include "window/sdl_window.hpp"
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
        m_textureFactory = new TextureManagerImpl(*this);
        m_effectFactory = new EffectFactory(*this);
        m_windowManager = new SDLWindowManager();

#if __APPLE__ && USE_METAL
        m_renderer = new MetalRenderer(*this);
        // m_materialFactory = new MetalMaterialFactory(*this);
        m_meshFactory = new MetalMeshFactory(*this);
        m_spriteRenderer = new MetalSpriteRenderer(*this);
#elif WIN32 && USE_D3D11
        m_renderer = new D3D11Renderer(*m_windowManager);
        // m_materialFactory = new D3D11MaterialFactory(*this);
        // m_meshFactory = new D3D11MeshFactory(*this);
        // m_spriteRenderer = new D3D11SpriteRenderer(*this);
#else
        m_renderer = new WebGPURenderer(*this);
        m_materialFactory = new WebGPUMaterialFactory(*this);
        m_meshFactory = new WebGPUMeshFactory(*this);
        m_spriteRenderer = new WebGPUSpriteRenderer(*this);
#endif
    }

    Framework::~Framework()
    {
    }

    void Framework::Initialize(WindowParameters windowParameters, std::function<void()> callback)
    {
#if __APPLE__ && USE_METAL
        InitializeForMetal(windowParameters);
        m_spriteRenderer->Initialize();
#elif WIN32 && USE_D3D11
        InitializeForD3D11(windowParameters);
#else
        InitializeForWGPU(windowParameters);
        m_spriteRenderer->Initialize();
#endif


        callback();
    }

    void Framework::InitializeForWGPU(WindowParameters windowParameters)
    {
        WGPUInstance instance;
        WGPUSurface surface;
        m_windowManager->InitializeForWGPU(windowParameters, &instance, &surface);

        static_cast<WebGPURenderer *>(m_renderer)->Initialize(instance, surface);
    }

#ifdef __APPLE__
    void Framework::InitializeForMetal(WindowParameters windowParameters)
    {
        CA::MetalLayer *swapchain = m_windowManager->InitializeForMetal(windowParameters);
        static_cast<MetalRenderer *>(m_renderer)->Initialize(swapchain);
    }
#endif // __APPLE__

#ifdef WIN32
    void Framework::InitializeForD3D11(WindowParameters windowParameters)
    {
        HWND hwnd = m_windowManager->InitializeForD3D11(windowParameters);
        static_cast<D3D11Renderer *>(m_renderer)->Initialize(hwnd);
    }
#endif // WIN32

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
           //  wgpuDeviceTick(Context.WebGPUDevice);
// #endif
           
            m_renderer->BeginDraw();
            // m_spriteRenderer->BeginFrame();

            callback();
            
           //  m_spriteRenderer->EndFrame();
            m_renderer->EndDraw();

            SDL_Delay(16);
        }
    }
} // namespace BNS
