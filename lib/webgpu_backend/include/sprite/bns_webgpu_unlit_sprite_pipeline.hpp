#if USE_WEBGPU

#ifndef BNS_WEBGPU_UNLIT_SPRITE_PIPELINE

#define BNS_WEBGPU_UNLIT_SPRITE_PIPELINE

#include "Constants.hpp"
#include "texture/bns_webgpu_texture2d.hpp"
#include <vector>

#define FLOATS_PER_VERTEX 9
#define FLOATS_PER_INSTANCE (4 * FLOATS_PER_VERTEX)

namespace bns
{
    /// @brief The unlit sprite pipeline
    class WebGPUUnlitSpritePipeline final
    {
    private:
        WGPURenderPipeline m_pipeline;
        WGPUBindGroup m_projectionViewBindGroup;
        WGPUBindGroup m_sourceTextureBindGroup;
        WGPUBindGroup m_brightnessThresholdBindGroup;

        /// @brief Creates the projection view bind group layout.
        /// @param device The webgpu device.
        /// @param projectionViewBindGroupLayout The projection view bind group layout.
        /// @param projectionViewBuffer The projection view buffer.
        /// @return The projection view bind group layout.
        static WGPUBindGroup CreateProjectionViewBindGroup(WGPUDevice &device,
                                                           WGPUBindGroupLayout &projectionViewBindGroupLayout,
                                                           WGPUBuffer &projectionViewBuffer);

        /// @brief Creates the texture bind group.
        /// @param device The webgpu device.
        /// @param textureBindGroupLayout The texture bind group layout.
        /// @param texture The texture.
        /// @return The texture bind group.
        static WGPUBindGroup CreateTextureBindGroup(WGPUDevice &device,
                                                    WGPUBindGroupLayout &textureBindGroupLayout,
                                                    WebGPUTexture2D *texture);

        /// @brief Creates the brightness threshold bind group.
        /// @param device The webgpu device.
        /// @param brightnessThresholdBindGroupLayout The brightness threshold bind group layout.
        /// @param brightnessThresholdBuffer The brightness threshold buffer.
        /// @return The brightness threshold bind group.
        static WGPUBindGroup CreateBrightnessThresholdBindGroup(WGPUDevice &device,
                                                                WGPUBindGroupLayout &brightnessThresholdBindGroupLayout,
                                                                WGPUBuffer &brightnessThresholdBuffer);

    public:
        /// @brief The constructor.
        /// @param pipeline The pipeline.
        /// @param projectionViewBindGroup The projection view bind group.
        /// @param textureBindGroup The texture bind group.
        /// @param brightnessThresholdBindGroup The brightness threshold bind group.
        WebGPUUnlitSpritePipeline(WGPURenderPipeline pipeline,
                                  WGPUBindGroup projectionViewBindGroup,
                                  WGPUBindGroup textureBindGroup,
                                  WGPUBindGroup brightnessThresholdBindGroup);

        /// @brief The instance index which is used to tell how many instances are in buffer and to be drawn.
        u32 InstanceIndex;

        /// @brief The vertex buffer data.
        f32 DataArray[SPRITE_RENDERER_MAX_SPRITES_PER_DRAW * FLOATS_PER_INSTANCE];

        /// @brief Create a sprite pipeline
        /// @param device The webgpu device
        /// @param texture The texture to be used
        /// @param projectionViewBuffer The projection view buffer
        /// @param brightnessThresholdBuffer The brightness threshold buffer
        /// @return The sprite pipeline
        static WebGPUUnlitSpritePipeline *Create(
            WGPUDevice device,
            WebGPUTexture2D *texture,
            WGPUBuffer projectionViewBuffer,
            WGPUBuffer brightnessThresholdBuffer);

        /// @brief Gets the pipeline
        inline const WGPURenderPipeline &GetPipeline() const { return m_pipeline; }

        /// @brief Gets the global bind group
        inline const WGPUBindGroup &GetProjectionViewBindGroup() const { return m_projectionViewBindGroup; }

        /// @brief Gets the texture bind group
        inline const WGPUBindGroup &GetTextureBindGroup() const { return m_sourceTextureBindGroup; }

        /// @brief Gets the brightness threshold bind group
        inline const WGPUBindGroup &GetBrightnessThresholdBindGroup() const { return m_brightnessThresholdBindGroup; }
    };
}

#endif

#endif