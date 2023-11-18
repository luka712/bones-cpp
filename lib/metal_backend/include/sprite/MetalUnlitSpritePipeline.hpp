#if USE_METAL

#ifndef BNS_METAL_UNLIT_SPRITE_PIPELINE_HPP

#define BNS_METAL_UNLIT_SPRITE_PIPELINE_HPP

#include "Constants.hpp"
#include "texture/MetalTexture2D.hpp"
#include <vector>
#include "BnsMetal.hpp"
#include "renderer/MetalRenderer.hpp"

#define FLOATS_PER_VERTEX 9
#define FLOATS_PER_INSTANCE (4 * FLOATS_PER_VERTEX)

namespace bns
{
    class MetalUnlitSpritePipeline final
    {
    private:
        MTL::RenderPipelineState *m_pipeline;
        MetalTexture2D *m_texture;

    public:
        MetalUnlitSpritePipeline(MTL::RenderPipelineState *pipeline, MetalTexture2D *texture);

        /// @brief The instance index which is used to tell how many instances are in buffer and to be drawn.
        u32 InstanceIndex;

        /// @brief The vertex buffer data.
        f32 DataArray[SPRITE_RENDERER_MAX_SPRITES_PER_DRAW * FLOATS_PER_INSTANCE];

        /// @brief Create a sprite pipeline
        /// @param device The webgpu device
        /// @param texture The texture to be used
        /// @return The sprite pipeline
        static MetalUnlitSpritePipeline *Create(MetalRenderer &renderer, MetalTexture2D *texture);

        /**
         * @brief Gets the pipeline
         */
        inline const MTL::RenderPipelineState *GetPipeline() const { return m_pipeline; }

        /**
         * @brief Gets the texture
         */
        inline const MetalTexture2D *GetTexture() const { return m_texture; }
    };
}

#endif // BNS_METAL_UNLIT_SPRITE_PIPELINE_HPP

#endif // USE_METAL