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

namespace bns
{
    Framework::Framework()
    {
        m_directory = new Directory();
        m_windowManager = new GLFWWindowManager();
        m_geometryBuilder = new GeometryBuilder();
        m_imageLoader = new ImageLoader(*m_directory);

        // WebGPU initialize
        bool wgpu = true;
        if(wgpu) {
            m_materialFactory = new WebGPUMaterialFactory(*this);
            m_meshFactory = new WebGPUMeshFactory(*this);
        }
        else {
            // m_materialFactory = new MetalMaterialFactory(*this);
            m_meshFactory = new MetalMeshFactory(*this);
        }
    }

    Framework::~Framework()
    {
    }

    void Framework::Initialize(WindowParameters windowParameters)
    {
        // InitializeForMetal(windowParameters);
        InitializeForWGPU(windowParameters);
    }

    void Framework::InitializeForWGPU(WindowParameters windowParameters)
    {

        // Initialize the window manager and get the WGPU instance and surface
        WGPUInstance instance;
        WGPUSurface surface;
        m_windowManager->InitializeForWGPU(windowParameters, &instance, &surface);

        WebGPURenderer renderer(*this);
        renderer.Initialize(instance, surface);

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

        while (!glfwWindowShouldClose(((GLFWWindowManager *)m_windowManager)->m_window))
        {
            // Do nothing, this checks for ongoing asynchronous operations and call their callbacks
            // NOTE: this is specific to DAWN and is not part of WebGPU standard.
            wgpuDeviceTick(Context.WebGPUDevice);

            glfwPollEvents();
            camera.Update(0.0f);

            renderer.BeginDraw();

            testMaterial->Draw(camera, testMesh);

            renderer.EndDraw();
        }

        renderer.Destroy();
    }

    void Framework::InitializeForMetal(WindowParameters windowParameters)
    {
        m_windowManager = new SDLWindowManager();

        CA::MetalLayer *swapchain = m_windowManager->InitializeForMetal(windowParameters);

        // TEMPORARY CODE
        MetalRenderer renderer(*this);
        renderer.Initialize(swapchain);

        Mesh *mesh = m_meshFactory->CreateQuadMesh();

          // TEST DATA
        MetalTexture2D *testTexture = new MetalTexture2D(*this, m_imageLoader->LoadImage("assets/uv_test.png"));
        testTexture->Initialize();

        MetalBasicMeshTexturedTestMaterial *testMaterial = new MetalBasicMeshTexturedTestMaterial(*this, testTexture);
        testMaterial->Initialize();

        bool quit = false;
        SDL_Event event;

        FreeCamera camera;

        while (!quit)
        {
            // Process events
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    quit = true;
                }

                renderer.BeginDraw();

                testMaterial->Draw(camera, mesh);

                renderer.EndDraw();

                SDL_Delay(16);
            }

            // // Define the vertices for the triangle
            // std::vector<float> vertices = {
            //     -0.5f, -0.5f, 0.0f, // Vertex 1
            //     0.5f, -0.5f, 0.0f,  // Vertex 2
            //     0.0f, 0.5f, 0.0f    // Vertex 3
            // };

            // MTL::Device *device = swapchain->device();

            // // Create a vertex buffer
            // MTL::ResourceOptions options = 0;
            // MTL::Buffer *vertexBuffer = device->newBuffer(vertices.data(), vertices.size() * sizeof(float), options);

            // // NS::String *name = device->name();
            // // std::cerr << "device name: " << name->utf8String() << std::endl;

            // // Event loop
            // bool quit = false;
            // SDL_Event event;
            // while (!quit)
            // {
            //     // Process events
            //     while (SDL_PollEvent(&event))
            //     {
            //         if (event.type == SDL_QUIT)
            //         {
            //             quit = true;
            //         }
            //     }

            //     // Render or update your game/application here
            //     auto drawable = swapchain->nextDrawable();

            //     Color color = Color::LightPink();
            //     MTL::ClearColor clear_color(color.R, color.G, color.B, 1.0);
            //     MTL::RenderPassDescriptor *pass = MTL::RenderPassDescriptor::renderPassDescriptor();

            //     auto color_attachment = pass->colorAttachments()->object(0);
            //     color_attachment->setClearColor(clear_color);
            //     color_attachment->setLoadAction(MTL::LoadAction::LoadActionClear);
            //     color_attachment->setStoreAction(MTL::StoreAction::StoreActionStore);
            //     color_attachment->setTexture(drawable->texture());

            //     MTL::CommandQueue *queue = device->newCommandQueue();

            //     MTL::CommandBuffer *buffer = queue->commandBuffer();

            //     MTL::RenderCommandEncoder *encoder = buffer->renderCommandEncoder(pass);

            //     encoder->setVertexBuffer(vertexBuffer, 0, 0);
            //     NS::UInteger vertexCount = 1;
            //     NS::UInteger vertexStart = 0;
            //     encoder->drawPrimitives(MTL::PrimitiveType::PrimitiveTypeTriangle, vertexStart, vertexCount);
            //     encoder->setViewport(MTL::Viewport{
            //         0.0f, 0.0f,
            //         (double)windowParameters.Width, (double)windowParameters.Height,
            //         0.0f, 1.0f});
            //     encoder->endEncoding();
            //     buffer->presentDrawable(drawable);
            //     buffer->commit();

            //     drawable->release();

            //     // Delay to manage frame rate (optional)
            //     SDL_Delay(16);
        }
    }
} // namespace BNS
