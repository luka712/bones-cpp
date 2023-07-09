#include "Framework.hpp"
#include <vector>
#include "renderer/MetalRenderer.hpp"
#include "renderer/WebGPURenderer.hpp"
#include "window/sdl_window.hpp"
#include "window/glfw_window.hpp"
#include "material/WebGPUMaterialFactory.hpp"
#include "mesh/wgpu/WebGPUMeshFactory.hpp"
#include "renderer/common/WebGPURenderPipelineUtil.hpp"
#include "camera/FreeCamera.hpp"
#include "material/basic/wgpu/WebGPUNoMeshTestMaterial.hpp"

namespace bns
{

    Framework::Framework()
    {
        m_windowManager = new GLFWWindowManager();
        m_geometryBuilder = new GeometryBuilder();

        // WebGPU initialize
        MaterialFactory = new WebGPUMaterialFactory(*this);
        m_meshFactory = new WebGPUMeshFactory(*this);
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
        WebGPUTestNoMeshMaterial *testMaterial = new WebGPUTestNoMeshMaterial(*this);
        testMaterial->Initialize();

        while (!glfwWindowShouldClose(((GLFWWindowManager *)m_windowManager)->m_window))
        {
            glfwPollEvents();
            camera.Update(0.0f);

            renderer.BeginDraw();

            testMaterial->Draw(camera, nullptr);

            renderer.EndDraw();
        }

        renderer.Destroy();
    }

    void Framework::InitializeForMetal(WindowParameters windowParameters)
    {
        m_windowManager = new SDLWindowManager();

        CA::MetalLayer *swapchain = m_windowManager->InitializeForMetal(windowParameters);

        // TEMPORARY CODE
        MetalRenderer renderer;
        renderer.Initialize(swapchain);

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

                renderer.BeginDraw();

                // TODO: stuff here

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
