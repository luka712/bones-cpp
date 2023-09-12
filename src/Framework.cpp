#include "Framework.hpp"
#include <vector>
#include "renderer/MetalRenderer.hpp"
#include "renderer/WebGPURenderer.hpp"
#include "window/sdl_window.hpp"
#include "window/glfw_window.hpp"
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
        m_windowManager = new GLFWWindowManager();
        m_geometryBuilder = new GeometryBuilder();
        m_imageLoader = new ImageLoader(*m_directory);
        m_bitmapSpriteFontLoader = new BitmapSpriteFontLoader(*this);

        // WebGPU initialize
#if __APPLE__ && USE_METAL
        // m_materialFactory = new MetalMaterialFactory(*this);
        m_meshFactory = new MetalMeshFactory(*this);
        m_spriteRenderer = new MetalSpriteRenderer(*this);
#else
        m_materialFactory = new WebGPUMaterialFactory(*this);
        m_meshFactory = new WebGPUMeshFactory(*this);
        m_spriteRenderer = new WebGPUSpriteRenderer(*this);
#endif
    }

    Framework::~Framework()
    {
    }

    void Framework::Initialize(WindowParameters windowParameters)
    {
#if __APPLE__ && USE_METAL
        InitializeForMetal(windowParameters);
#else
        InitializeForWGPU(windowParameters);
#endif
    }

    void Framework::InitializeForWGPUGLFW(WindowParameters windowParameters)
    {

        // Initialize the window manager and get the WGPU instance and surface
        WGPUInstance instance;
        WGPUSurface surface;
        m_windowManager->InitializeForWGPU(windowParameters, &instance, &surface);

        WebGPURenderer renderer(*this);
        renderer.Initialize(instance, surface);

        m_spriteRenderer->Initialize();

        // Mesh *mesh = m_meshFactory->CreateTriangleMesh();
        // Material *material = MaterialFactory->CreateBasicMaterial();
        // mesh->AddMaterial(material);

        FreeCamera camera;

        // TEST DATA
        WebGPUTexture2D *testTexture = new WebGPUTexture2D(*this, m_imageLoader->LoadImage("assets/uv_test.png"));
        testTexture->Initialize();

        WebGPUBasicMeshTexturedTestMaterial *testMaterial = new WebGPUBasicMeshTexturedTestMaterial(*this, testTexture);
        testMaterial->Initialize();

        Mesh *testMesh = m_meshFactory->CreateQuadMesh(true);

        static f32 rotation = 0.0f;

        while (!glfwWindowShouldClose(((GLFWWindowManager *)m_windowManager)->m_window))
        {
            // Do nothing, this checks for ongoing asynchronous operations and call their callbacks
            // NOTE: this is specific to DAWN and is not part of WebGPU standard.
            wgpuDeviceTick(Context.WebGPUDevice);

            glfwPollEvents();
            camera.Update(0.0f);

            renderer.BeginDraw();
            m_spriteRenderer->BeginFrame();

            i32 hw = testTexture->GetWidth() / 2;
            i32 hh = testTexture->GetHeight() / 2;

            rotation += 0.1;
            Vec2f rotationOrigin = Vec2f(0.5f, 0.5f);

            // whole texture
            m_spriteRenderer->Draw(testTexture, Rect(0, 0, 100, 100));

            // top left quadrant
            m_spriteRenderer->Draw(testTexture, Rect(100, 0, 100, 100), Rect(0, 0, hw, hh), Color::White(), rotation, rotationOrigin);

            // top right quadrant
            m_spriteRenderer->Draw(testTexture, Rect(200, 0, 100, 100), Rect(hw, 0, hw, hh), Color::White(), rotation, rotationOrigin);

            // bottom left quadrant
            m_spriteRenderer->Draw(testTexture, Rect(100, 100, 100, 100), Rect(0, hh, hw, hh), Color::White(), rotation, rotationOrigin);

            // bottom right quadrant
            m_spriteRenderer->Draw(testTexture, Rect(200, 100, 100, 100), Rect(hw, hh, hw, hh), Color::White(), rotation, rotationOrigin);

            //    testMaterial->Draw(camera, testMesh);

            m_spriteRenderer->EndFrame();
            renderer.EndDraw();
        }

        renderer.Destroy();
    }

    void Framework::InitializeForWGPU(WindowParameters windowParameters)
    {
        m_windowManager = new SDLWindowManager();

        WGPUInstance instance;
        WGPUSurface surface;
        m_windowManager->InitializeForWGPU(windowParameters, &instance, &surface);

        WebGPURenderer renderer(*this);
        renderer.Initialize(instance, surface);

        SpriteFont *font = GetBitmapSpriteFontLoader().LoadSnowBImpl("assets/SpriteFont.xml", "assets/SpriteFont.png");

        m_spriteRenderer->Initialize();

        Mesh *mesh = m_meshFactory->CreateQuadMesh();

        // TEST DATA
        WebGPUTexture2D *testTexture = new WebGPUTexture2D(*this, m_imageLoader->LoadImage("assets/uv_test.png"));
        testTexture->Initialize();

        WebGPUBasicMeshTexturedTestMaterial *testMaterial = new WebGPUBasicMeshTexturedTestMaterial(*this, testTexture);
        testMaterial->Initialize();

        bool quit = false;
        SDL_Event event;

        FreeCamera camera;

        static f32 rotation = 0.0f;

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

            renderer.BeginDraw();

            // testMaterial->Draw(camera, mesh);
            m_spriteRenderer->BeginFrame();

            i32 hw = testTexture->GetWidth() / 2;
            i32 hh = testTexture->GetHeight() / 2;

            rotation += 0.1;
            Vec2f rotationOrigin = Vec2f(0.5f, 0.5f);

            m_spriteRenderer->DrawString(font, "Hello World!", Vec2f(300, 300), Color::White(), 1.0f);

            // whole texture
            m_spriteRenderer->Draw(testTexture, Rect(0, 0, 100, 100));

            // top left quadrant
            m_spriteRenderer->Draw(testTexture, Rect(100, 0, 100, 100), Rect(0, 0, hw, hh), Color::White(), rotation, rotationOrigin);

            // top right quadrant
            m_spriteRenderer->Draw(testTexture, Rect(200, 0, 100, 100), Rect(hw, 0, hw, hh), Color::White(), rotation, rotationOrigin);

            // bottom left quadrant
            m_spriteRenderer->Draw(testTexture, Rect(100, 100, 100, 100), Rect(0, hh, hw, hh), Color::White(), rotation, rotationOrigin);

            // bottom right quadrant
            m_spriteRenderer->Draw(testTexture, Rect(200, 100, 100, 100), Rect(hw, hh, hw, hh), Color::White(), rotation, rotationOrigin);

            m_spriteRenderer->EndFrame();

            renderer.EndDraw();

            SDL_Delay(16);
        }
    }

    void Framework::InitializeForMetal(WindowParameters windowParameters)
    {
        m_windowManager = new SDLWindowManager();

        CA::MetalLayer *swapchain = m_windowManager->InitializeForMetal(windowParameters);

        // TEMPORARY CODE
        MetalRenderer renderer(*this);
        renderer.Initialize(swapchain);

        SpriteFont *font = GetBitmapSpriteFontLoader().LoadSnowBImpl("assets/SpriteFont.xml", "assets/SpriteFont.png");

        m_spriteRenderer->Initialize();

        Mesh *mesh = m_meshFactory->CreateQuadMesh();

        // TEST DATA
        MetalTexture2D *testTexture = new MetalTexture2D(*this, m_imageLoader->LoadImage("assets/uv_test.png"));
        testTexture->Initialize();

        MetalBasicMeshTexturedTestMaterial *testMaterial = new MetalBasicMeshTexturedTestMaterial(*this, testTexture);
        testMaterial->Initialize();

        bool quit = false;
        SDL_Event event;

        FreeCamera camera;

        static f32 rotation = 0.0f;

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

            renderer.BeginDraw();

            // testMaterial->Draw(camera, mesh);
            m_spriteRenderer->BeginFrame();

            i32 hw = testTexture->GetWidth() / 2;
            i32 hh = testTexture->GetHeight() / 2;

            rotation += 0.1;
            Vec2f rotationOrigin = Vec2f(0.5f, 0.5f);

            m_spriteRenderer->DrawString(font, "Hello World!", Vec2f(300, 300), Color::White(), 1.0f);

            // whole texture
            m_spriteRenderer->Draw(testTexture, Rect(0, 0, 100, 100));

            // top left quadrant
            m_spriteRenderer->Draw(testTexture, Rect(100, 0, 100, 100), Rect(0, 0, hw, hh), Color::White(), rotation, rotationOrigin);

            // top right quadrant
            m_spriteRenderer->Draw(testTexture, Rect(200, 0, 100, 100), Rect(hw, 0, hw, hh), Color::White(), rotation, rotationOrigin);

            // bottom left quadrant
            m_spriteRenderer->Draw(testTexture, Rect(100, 100, 100, 100), Rect(0, hh, hw, hh), Color::White(), rotation, rotationOrigin);

            // bottom right quadrant
            m_spriteRenderer->Draw(testTexture, Rect(200, 100, 100, 100), Rect(hw, hh, hw, hh), Color::White(), rotation, rotationOrigin);

            m_spriteRenderer->EndFrame();

            renderer.EndDraw();

            SDL_Delay(16);
        }
    }
} // namespace BNS
