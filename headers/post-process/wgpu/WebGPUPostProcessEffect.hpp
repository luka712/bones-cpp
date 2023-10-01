#ifndef BNS_WEBGPU_POST_PROCESS_EFFECT_HPP

#define BNS_WEBGPU_POST_PROCESS_EFFECT_HPP

#include "post-process/PostProcessEffect.hpp"
#include "textures/wgpu/WebGPUTexture2D.hpp"
#include <string>

/**
 * Each effects should at least have a vertex shader and a fragment shader
 * to draw a full screen quad.
 * Input into fragment shader should be a texture and texture coordinates which represent what was drawn so far to screen.
 */

namespace bns
{
    class Framework;

    class WebGPUPostProcessEffect : public PostProcessEffect
    {
    protected:
        /**
         * The device. Fetched in initialize.
         */
        WGPUDevice m_device;

        WGPURenderPipeline m_pipeline; // post process shaders pipeline
        WGPUBuffer m_vertexBuffer;     // for screen geometry

        // for source texture, assumes defaults.
        // Source texture is usually the texture that represents what was to be drawn so far to screen.
        WGPUBindGroupLayout m_sourceTextureBindGroupLayout; // for the source texture which comes into draw
        WGPUBindGroup m_sourceTextureBindGroup;             // for the source texture which comes into draw

        /**
         * @brief Create a vertex buffer for a full screen quad.
         * Buffer is created as an array buffer (no indices).
         * Holds 6 vertices (2 triangles) with 2 floats for position and 2 floats for texture coordinates.
         */
        virtual WGPUBuffer CreateVertexBuffer();

        /**
         * @brief Create a bind group layouts for the post process effect.
         * By default creates the layout for the source texture.
         * The source texture is the texture which comes into draw.
         * Holds slot 0 for the source texture sampler.
         * Holds slot 1 for the source texture.
         * 
         * note 
         * m_sourceTextureBindGroupLayout is assigned by default in parent. 
         * Override to create additional layouts.
         * Best to override by calling parent method and adding to the result.
         * 
         * @return The bind group layout for the post process effect.
         */
        virtual std::vector<WGPUBindGroupLayout> CreateBindGroupLayouts();

        /**
         * @brief Create a bind groups.
         * By default it is created for the source texture.
         * The source texture is the texture which comes into draw.
         * Holds slot 0 for the source texture.
         * Holds slot 1 for the source texture sampler.
         * 
         * @param bindGroupLayouts The bind group layouts created by CreateBindGroupLayouts.
         * 
         * note
         * m_sourceTextureBindGroup is assigned by default in parent.
         * Override to create additional bind groups.
         * Best to override by calling parent method and adding to the result.
         * 
         * @return The bind groups.
         */
        virtual std::vector<WGPUBindGroup> CreateBindGroups(std::vector<WGPUBindGroupLayout> bindGroupLayouts);

        /**
         * @brief Create a render pipeline for the post process effect.
         * By default simple pipeline is provided which assumes that it takes a texture and draws it to screen.
         * 
         * @param bindGroupLayouts The bind group layouts created by CreateBindGroupLayouts.
         */
        virtual WGPURenderPipeline CreateRenderPipeline(std::vector<WGPUBindGroupLayout> bindGroupLayouts);

        /**
         * @brief Get the shader path for the post process effect.
         */
        virtual std::string GetShaderPath() = 0;

    public:
        WebGPUPostProcessEffect(const Framework &framework);

        void Initialize() override;


         /**
         * @brief Draw the effect to the destination texture.
         * @param destinationTexture The destination texture. In this case it is of type WGPUTextureView.
         * This is a texture to which we want to render, usually the screen texture.
         * But can be any other texture if there are multiple post process effects.
         */
        void Draw(void *destinationTexture) override;
    };
} // namespace bns

#endif // !BNS_WEBGPU_POST_PROCESS_EFFECT_HPP