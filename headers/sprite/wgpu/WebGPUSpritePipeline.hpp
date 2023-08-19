#ifndef BNS_WEBGPU_SPRITE_PIPELINE

#define BNS_WEBGPU_SPRITE_PIPELINE

#include "Constants.hpp"
#include "textures/wgpu/WebGPUTexture2D.hpp"
#include <vector>

#define FLOATS_PER_VERTEX 9
#define FLOATS_PER_INSTANCE (4 * FLOATS_PER_VERTEX)

namespace bns
{
    class WebGPUSpritePipeline final
    {
    private:
        WGPURenderPipeline m_pipeline;
        WGPUBindGroup m_projectionViewBindGroup;
        WGPUBindGroup m_textureBindGroup;

    public:
       WebGPUSpritePipeline(WGPURenderPipeline pipeline, WGPUBindGroup projectionViewBindGroup, WGPUBindGroup textureBindGroup);

        /**
         * @brief The instance index which is used to tell how many instances are in buffer and to be drawn.
         */
        u32 InstanceIndex;

        /**
         * @brief The vertex buffer data.
        */
        f32 DataArray[SPRITE_RENDERER_MAX_SPRITES_PER_DRAW * FLOATS_PER_INSTANCE];

        /**
         * @brief Create a sprite pipeline
         * @param device The webgpu device
         * @param texture The texture to be used
         * @return The sprite pipeline
         */
        static WebGPUSpritePipeline *Create(WGPUDevice device,  WebGPUTexture2D* texture, WGPUBuffer projectionViewBuffer);

        /**
         * @brief Gets the pipeline
         */
        inline const WGPURenderPipeline &GetPipeline() const { return m_pipeline; }

        /**
         * @brief Gets the global bind group
         */
        inline const WGPUBindGroup &GetProjectionViewBindGroup() const { return m_projectionViewBindGroup; }

        /**
         * @brief Gets the texture bind group
         */
        inline const WGPUBindGroup &GetTextureBindGroup() const { return m_textureBindGroup; }
    };
}

#endif