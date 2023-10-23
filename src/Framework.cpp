#include "Framework.hpp"
#include <vector>
#include "renderer/metal/MetalRenderer.hpp"
#include "renderer/wgpu/WebGPURenderer.hpp"
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
#include "textures/wgpu/WebGPUTexture2D.hpp"
#include "textures/metal/MetalTexture2D.hpp"
#include "sprite/wgpu/WebGPUSpriteRenderer.hpp"
#include "sprite/metal/MetalSpriteRenderer.hpp"

namespace bns
{
    Framework::Framework()
    {
        m_directory = new Directory();
        m_geometryBuilder = new GeometryBuilder();
        m_imageLoader = new ImageLoader(*m_directory);
        m_bitmapSpriteFontLoader = new BitmapSpriteFontLoader(*this);
        m_textureFactory = new TextureManager(*this);
        m_effectFactory = new EffectFactory(*this);
        m_windowManager = new SDLWindowManager();

#if __APPLE__ && USE_METAL
        m_renderer = new MetalRenderer(*this);
        // m_materialFactory = new MetalMaterialFactory(*this);
        m_meshFactory = new MetalMeshFactory(*this);
        m_spriteRenderer = new MetalSpriteRenderer(*this);
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
#else
        InitializeForWGPU(windowParameters);
#endif
        m_spriteRenderer->Initialize();

        callback();
    }

    void Framework::InitializeForWGPU(WindowParameters windowParameters)
    {
        WGPUInstance instance;
        WGPUSurface surface;
        m_windowManager->InitializeForWGPU(windowParameters, &instance, &surface);

        static_cast<WebGPURenderer *>(m_renderer)->Initialize(instance, surface);
    }

    void Framework::InitializeForMetal(WindowParameters windowParameters)
    {
        CA::MetalLayer *swapchain = m_windowManager->InitializeForMetal(windowParameters);
        static_cast<MetalRenderer *>(m_renderer)->Initialize(swapchain);
    }

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
           //  wgpuDeviceTick(Context.WebGPUDevice);
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
