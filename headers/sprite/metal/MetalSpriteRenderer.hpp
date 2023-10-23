#ifndef BNS_METAL_SPRITE_RENDERER_HPP

#define BNS_METAL_SPRITE_RENDERER_HPP

#include "data/Types.hpp"
#include "sprite/metal/MetalSpritePipeline.hpp"
#include "sprite/SpriteRenderer.hpp"
#include "font/SpriteFont.hpp"
#include <Metal/Metal.hpp>
#include <map>
#include <stack>

namespace bns
{
    class Framework;

    /**
     * @brief The Metal implementation of sprite renderer.
     */
    class MetalSpriteRenderer final : public SpriteRenderer
    {
    private:
        /// @brief The framework.
        Framework &m_framework;

        /**
         * @brief The device.
         */
        MTL::Device *m_device;

        /**
         * @brief The index buffer.
         */
        MTL::Buffer *m_indexBuffer;

        
        /// @brief The projection view matrix buffer.
        MTL::Buffer *m_projectionViewMatrixBuffer;

        /// @brief The brightness threshold buffer.
        MTL::Buffer* m_brightnessThresholdBuffer;

        /// @brief The ambient light buffer.
        MTL::Buffer* m_ambientLightBuffer;

        /**
         * @brief All the allocated pipelines per texture. Pop from this pipeline to current draw pipelines.
         * At the end of frame, push back to this pipeline from current draw pipelines.
         */
        std::map<u32, std::stack<MetalSpritePipeline *>> m_allocatedPipelines;

        /**
         * @brief The current draw pipelines per texture. At the end of frame pop from this pipeline to allocated pipelines.
         * If there is no allocated pipeline, create a new one and push it here.
         */
        std::map<u32, std::stack<MetalSpritePipeline *>> m_currentDrawPipelines;

        /**
         * @brief The stack of vertex buffers.
         */
        std::stack<MTL::Buffer *> m_vertexBufferStack;

        /**
         * @brief Setup of the index buffer.
         */
        void SetupIndexBuffer();

        /**
         * @brief Gets or creates a pipeline for the texture.
         * Creation is handled internally, so just get reference.
         */
        MetalSpritePipeline &GetPipeline(MetalTexture2D *texture);

    public:
        /**
         * The constructor.
         */
        MetalSpriteRenderer(Framework &framework);

        void Initialize() override;

        void BeginFrame() override;

        void Draw(Texture2D *texture,
                  const Rect &drawRect,
                  const Rect &sourceRect,
                  const Color &color,
                  f32 rotationInRadians, const Vec2f &rotationOrigin) override;

        void DrawString(SpriteFont *font,
                        const std::string &text,
                        const Vec2f &position,
                        const Color &color,
                        const f32 scale) override;

        void EndFrame() override;
    };
}

#endif