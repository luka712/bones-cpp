#if USE_WEBGPU

#ifndef BNS_RENDERER_WGPU_HPP

#define BNS_RENDERER_WGPU_HPP

#include "bns_webgpu.hpp"
#include "bns_math.hpp"
#include "renderer/bns_renderer.hpp"
#include "texture/bns_texture_manager.hpp"
#include "Window.hpp"
#include <functional>

namespace bns
{
    class WebGPURenderer final : public Renderer
    {
    private:
        /// @brief The framework.
        WindowManager *m_windowManager;

        /// @brief The instance is a class in WebGPU. It is responsible for creating a surface.
        /// Instance in this context is a collection of adapters.
        WGPUInstance m_instance;

        /**
         * @brief WGPUSurface is a class in WebGPU. It is responsible for creating a surface.
         * Surface in this context is a canvas that can be drawn on.
         * It is similar to a window in DirectX.
         * It is similar to a CAMetalLayer in Metal.
         * It is similar to a window in OpenGL.
         * It is similar to a window in Vulkan.
         */
        WGPUSurface m_surface;

        /**
         * @brief WGPUAdapter is a class in WebGPU. It is responsible for creating a device.
         */
        WGPUAdapter m_adapter;

        /**
         * @brief WGPUAdapter is a class in WebGPU. It is responsible for creating a device.
         * Device in this context is a GPU.
         * It is similar to a device in Metal.
         * It is similar to a physical device in Vulkan.
         */
        WGPUDevice m_device;

        /// @brief The queue.
        WGPUQueue m_queue;

        /**
         * @brief WGPUSwapChain is a class in WebGPU. It is responsible for creating a swap chain.
         * Swap chain in this context is a collection of buffers that can be drawn on.
         * It is similar to a back buffer in DirectX.
         * It is similar to a drawable in Metal.
         * It is similar to a frame buffer in OpenGL.
         * It is similar to a frame buffer in Vulkan.
         */
        WGPUSwapChain m_swapChain;

        /// @brief The blit command encoder. Used to copy textures, buffers, etc.
        /// Persist only for one frame and it cleared when called. Always should be called at start of frame.
        /// Mainly used to create GPU only buffer from shared CPU/GPU buffer.
        WGPUCommandEncoder m_blitCommandEncoder;

        /**
         * @brief WGPUCommandEncoder is a class in WebGPU. It is responsible for creating a command encoder.
         * Command encoder in this context is a collection of commands that can be executed.
         * It is similar to a command buffer in Metal.
         * It is similar to a command buffer in Vulkan.
         * It is similar to a command buffer in DirectX.
         */
        WGPUCommandEncoder m_drawCommandEncoder;

        /**
         * @brief WGPURenderPassEncoder is a class in WebGPU. It is responsible for creating a render pass encoder.
         * Render pass encoder in this context is a collection of commands that can be executed.
         * It is similar to a command buffer in Metal.
         * It is similar to a command buffer in Vulkan.
         * It is similar to a command buffer in DirectX.
         */
        WGPURenderPassEncoder m_currentPassEncoder;

        /**
         * @brief WGPUTextureView is a class in WebGPU. It is texture fetched on begining of frame to which we draw.
         * Texture view in this context is a texture that can be drawn on.
         * It is similar to a drawable in Metal.
         * It is similar to a frame buffer in OpenGL.
         * It is similar to a frame buffer in Vulkan.
         * It is similar to a back buffer in DirectX.
         */
        WGPUTextureView m_currentTextureView;

        /// @brief The brightness texture view. Is create from @ref m_brightnessTexture.
        /// Will be null if @ref m_brightnessTexture is null.
        WGPUTextureView m_brightnessTextureView;


        // Used for operations that require blit command encoder. For example, copying textures, copying buffers, etc.
        // This will be cleared after the operation is done and persist only for the first frame.
        std::vector<std::function<void(WGPUCommandEncoder)>> m_onBlitCommandEncoderAvailable;

        /**
         * Creates the webgpu adapter.
         */
        WGPUAdapter CreateAdapter();

        /// @brief Creates the webgpu device.
        WGPUDevice CreateDevice();

        /// @brief Resizes the swap chain.
        void Resize();

        /// @brief On start of frame blit command encoder is available and all registered callbacks are called.
        /// Called at start of frame and endeded after all registered callbacks are called at start of frame. Always should
        /// run at start of frame before rendering command encoder and then CommandEncoder is available to registered
        /// callbacks. After all callbacks are called, CommandEncoder is ended and released.
        void HandleBlitCommands();

    public:
        /// @brief Gets the renderer type.
        /// @return The renderer type.
        RendererType GetRendererType() const override { return RendererType::WebGPU; }

        /// @brief The constructor.
        /// @param windowManager The window manager.
        WebGPURenderer(WindowManager *windowManager);

        WGPUSwapChain GetSwapChain() const { return m_swapChain; }

        /// @brief Gets the device.
        /// @return The device.
        WGPUDevice GetDevice() const { return m_device; }

        /// @brief Gets the queue.
        /// @return The queue.
        WGPUQueue GetQueue() const { return m_queue; }

        /// @brief Gets the blit command encoder.
        /// @return The blit command encoder.
        WGPUCommandEncoder GetBlitCommandEncoder() const { return m_blitCommandEncoder; }

        WGPUCommandEncoder GetDrawCommandEncoder() const { return m_drawCommandEncoder; }

        /// @brief Gets the current render pass encoder.
        /// @return The current WGPURenderPassEncoder.
        WGPURenderPassEncoder GetCurrentRenderPassEncoder() const { return m_currentPassEncoder; }

        /**
         * @brief Gets the view into swap chain texture.
         */
        void *GetSwapChainTexture() override;

        void Initialize(WGPUInstance instance, WGPUSurface surface);
        void BeginDraw() override;
        void EndDraw() override;
        void Destroy() override;

        /// @brief On blit command encoder available.
        // This is used for operations that require blit command encoder. For example, copying textures, copying buffers, etc.
        // Persist only for one frame and it cleared when called.
        /// @param onBlitCommandEncoderAvailable The function to call when the blit command encoder is available.
        void OnBlitCommandEncoderAvailable(std::function<void(WGPUCommandEncoder)> onBlitCommandEncoderAvailable);
    };
} // namespace BNS

#endif // !BNS_RENDERER_WGPU_HPP

#endif // USE_WEBGPU