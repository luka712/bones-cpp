
#pragma once

#ifdef __APPLE__

#ifndef BNS_RENDERER_METAL_HPP

#define BNS_RENDERER_METAL_HPP

#include "renderer/Renderer.hpp"
#include "FileLoader.hpp"
#include "Window.hpp"
#include "BnsMetal.hpp"
#include "Vec2.hpp"
#include "Color.hpp"

namespace bns
{
    class MetalRenderer final : public Renderer
    {
    private:
        WindowManager* m_windowManager;

        /// @brief MetalLayer is a class in Apple's Metal
        /// framework that enables seamless integration of Metal rendering capabilities into a Core Animation layer hierarchy.
        CA::MetalLayer *m_metalLayer;

        /**
         * @brief Device is a class in Apple's Metal framework that represents a GPU device.
         * It is similar to Adapter/Device in the WebGPU API.
         * It is similar to a physical device in Vulkan.
         * It is similar to an adapter in DirectX.
         */
        MTL::Device *m_device;

        /**
         * @brief CommandQueue is a class in Apple's Metal framework that manages the scheduling and execution of command buffers.
         * It is similar to a command queue in WebGPU.
         */
        MTL::CommandQueue *m_queue;

        /**
         * @brief MetalDrawable is a protocol in the Metal framework that represents a drawable texture,
         * which can be used as a rendering destination for Metal commands.
         * It enables integration between Metal and higher-level frameworks like MetalKit for rendering graphics.
         * It is similar to Texture in the WebGPU API.
         * It is similar to a frame buffer in Vulkan.
         * It is similar to a back buffer in DirectX.
         */
        CA::MetalDrawable *m_currentDrawable;

        MTL::RenderCommandEncoder *m_renderCommandEncoder;

        MTL::CommandBuffer *m_commandBuffer;
        // MTL::RenderPipelineState *m_renderPipelineState;
        // MTL::Buffer *m_positionBuffer;
        // MTL::Buffer *m_colorsBuffer;

        void Resize();

    public:
        /// @brief Gets the device.
        /// @return The device object.
        MTL::Device* GetDevice() const { return m_device; }

        /// @brief Gets the command queue.
        /// @return The command queue object.
        MTL::CommandQueue* GetCommandQueue() const { return m_queue; }

        /// @brief Gets the render command encoder.
        /// @return The render command encoder object.
        MTL::RenderCommandEncoder* GetRenderCommandEncoder() const { return m_renderCommandEncoder; }

        MetalRenderer(WindowManager* windowManager);
        void Initialize(CA::MetalLayer *metalLayer);
        void BeginDraw() override;
        void EndDraw() override;
        void Destroy() override;

        /**
         * @brief Gets the view into swap chain texture.
         */
        void *GetSwapChainTexture() override;
    };
} // namespace BNS

#endif // !BNS_RENDERER_METAL_HPP
#endif // __APPLE__