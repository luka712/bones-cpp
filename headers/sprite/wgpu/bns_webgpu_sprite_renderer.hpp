#if USE_WEBGPU

#ifndef BNS_WEBGPU_UNLIT_SPRITE_RENDERER_HPP

#define BNS_WEBGPU_UNLIT_SPRITE_RENDERER_HPP

#include "sprite/bns_sprite_renderer.hpp"
#include "sprite/wgpu/WebGPUSpritePipeline.hpp"
#include <webgpu/webgpu.h>
#include <map>
#include <stack>
#include "renderer/bns_webgpu_renderer.hpp"

namespace bns
{
    /**
     * @brief The WebGPU implementation of sprite renderer.
     */
    class WebGPUSpriteRenderer final : public SpriteRenderer
    {
    private:
        /// @brief The renderer.
        WebGPURenderer *m_renderer;

        /// @brief The device.
        WGPUDevice m_device;

        /// @brief The index buffer.
        WGPUBuffer m_indexBuffer;

        /**
         * @brief The projection view matrix buffer.
         */
        WGPUBuffer m_projectionViewMatrixBuffer;

        /// @brief The brightness threshold buffer.
        WGPUBuffer m_brightnessThresholdBuffer;

        /// @brief The ambient light buffer.
        WGPUBuffer m_ambientLightBuffer;

        /// @brief The point light buffer.
        WGPUBuffer m_pointLightBuffer;

        /**
         * @brief All the allocated pipelines per texture. Pop from this pipeline to current draw pipelines.
         * At the end of frame, push back to this pipeline from current draw pipelines.
         */
        std::map<u32, std::stack<WebGPUSpritePipeline *>> m_allocatedPipelines;

        /**
         * @brief The current draw pipelines per texture. At the end of frame pop from this pipeline to allocated pipelines.
         * If there is no allocated pipeline, create a new one and push it here.
         */
        std::map<u32, std::stack<WebGPUSpritePipeline *>> m_currentDrawPipelines;

        /**
         * @brief The stack of vertex buffers.
         */
        std::stack<WGPUBuffer> m_vertexBufferStack;

        /**
         * @brief Setup of the index buffer.
         */
        void SetupIndexBuffer();

        /**
         * @brief Gets or creates a pipeline for the texture.
         * Creation is handled internally, so just get reference.
         */
        WebGPUSpritePipeline &GetPipeline(WebGPUTexture2D *texture);

    public:
        /// @brief The default constructor.
        WebGPUSpriteRenderer(Renderer *m_renderer);

        void Initialize() override;

        void BeginFrame() override;

        void Draw(Texture2D *texture,
                  const Rect &drawRect,
                  const Rect &sourceRect,
                  const Color &tintColor,
                  f32 rotationInRadians, const Vec2f &rotationOrigin) override;

        void DrawString(SpriteFont *font,
                        const std::string &text,
                        const Vec2f &position,
                        const Color &color,
                        f32 scale) override;

        void EndFrame() override;
    };
}

#endif

#endif 