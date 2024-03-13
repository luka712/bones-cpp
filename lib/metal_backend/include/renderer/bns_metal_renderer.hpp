#if USE_METAL

#ifndef BNS_METAL_RENDERER_HPP

#define BNS_METAL_RENDERER_HPP

#include "renderer/bns_renderer.hpp"
#include "loaders/bns_file_loader.hpp"
#include "Window.hpp"
#include "bns_metal.hpp"
#include "math/bns_vec2.hpp"
#include "bns_color.hpp"
#include <functional>

namespace bns
{
    /// @brief The metal renderer.
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

        /// @brief Blit command encoder is used for operations that require blit command encoder, such as copying textures, copying buffers, etc.
        /// For example for creating GPU only buffer, we create shared CPU/GPU buffer and then copy it to GPU only buffer.
        /// Blit command encoder is available at start of frame in our case and destroyed as soon as all events registered by OnBlitCommandEncoderAvailable
        /// are called. That way it ensures that no too command encoders are created. Render command encoder cannot exists if blit command encoder is not finished.
        MTL::BlitCommandEncoder *m_blitCommandEncoder;
        MTL::CommandBuffer *m_commandBuffer;

        // Used for operations that require blit command encoder. For example, copying textures, copying buffers, etc.
        // This will be cleared after the operation is done and persist only for the first frame.
        std::vector<std::function<void(MTL::BlitCommandEncoder*)>> m_onBlitCommandEncoderAvailable;

        /// @brief On start of frame blit command encoder is available and all registered callbacks are called.
        /// Called at start of frame and endeded after all registered callbacks are called at start of frame. Always should
        /// run at start of frame before rendering command encoder and then BlitCommandEncoder is available to registered 
        /// callbacks. After all callbacks are called, BlitCommandEncoder is ended and released.
        void HandleBlitCommands();

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

        /// @brief On blit command encoder available.
        // This is used for operations that require blit command encoder. For example, copying textures, copying buffers, etc.
        // Persist only for one frame and it cleared when called.
        /// @param onBlitCommandEncoderAvailable The function to call when the blit command encoder is available.
        void OnBlitCommandEncoderAvailable(std::function<void(MTL::BlitCommandEncoder*)> onBlitCommandEncoderAvailable);
    };
} // namespace BNS

#endif // !BNS_RENDERER_METAL_HPP
#endif // __APPLE__