
#pragma once

#if USE_METAL

#ifndef BNS_RENDERER_METAL_HPP

#define BNS_RENDERER_METAL_HPP

#include "renderer/bns_renderer.hpp"
#include "loaders/bns_file_loader.hpp"
#include "Window.hpp"
#include "bns_metal.hpp"
#include "math/bns_vec2.hpp"
#include "bns_color.hpp"

namespace bns
{
    class MetalRenderer final : public Renderer
    {
    private:
        WindowManager* m_windowManager;

        /// @brief MetalLayer is a class in Apple's Metal
        /// framework that enables seamless integration of Metal rendering capabilities into a Core Animation layer hierarchy.
        CA::MetalLayer *m_metalLayer;

        /// @brief MetalDrawable is a protocol in the Metal framework that represents a drawable texture,
        /// which can be used as a rendering destination for Metal commands.
        CA::MetalDrawable *m_currentDrawable;

        MTL::Device *m_device;
        MTL::CommandQueue *m_queue;
        MTL::RenderCommandEncoder *m_renderCommandEncoder;
        MTL::CommandBuffer *m_commandBuffer;

        void Resize();

    public:
        /// @brief Gets the renderer type.
        /// @return The renderer type.
        RendererType GetRendererType() const override { return RendererType::Metal; }

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

        /// @brief Initializes the renderer.
        /// @param metalLayer The metal layer. Provided by the window manager.
        void Initialize(CA::MetalLayer *metalLayer);
        void BeginDraw() override;
        void EndDraw() override;
        void Destroy() override;
    
        /// @brief Gets the view into swap chain texture.
        void *GetSwapChainTexture() override;
    };
} // namespace BNS

#endif // !BNS_RENDERER_METAL_HPP
#endif // __APPLE__