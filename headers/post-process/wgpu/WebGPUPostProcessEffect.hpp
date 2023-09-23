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
        WGPUBindGroupLayout m_textureBindGroupLayout; // for the source texture which comes into draw
        WGPUBindGroup m_textureBindGroup;             // for the source texture which comes into draw

        /**
         * @brief Create a vertex buffer for a full screen quad.
         * Buffer is created as an array buffer (no indices).
         * Holds 6 vertices (2 triangles) with 2 floats for position and 2 floats for texture coordinates.
         */
        virtual WGPUBuffer CreateVertexBuffer();

        /**
         * @brief Create a bind group for the source texture.
         * The source texture is the texture which comes into draw.
         * Holds slot 0 for the source texture.
         * Holds slot 1 for the source texture sampler.
         * @return The bind group for the source texture.
         */
        virtual WGPUBindGroup CreateTextureBindGroup();

        /**
         * @brief Create a bind group layout for the source texture.
         * The source texture is the texture which comes into draw.
         * Holds slot 0 for the source texture sampler.
         * Holds slot 1 for the source texture.
         */
        virtual WGPUBindGroupLayout CreateTextureBindGroupLayout();

        /**
         * @brief Create a render pipeline for the post process effect.
         * By default simple pipeline is provided which assumes that it takes a texture and draws it to screen.
         */
        virtual WGPURenderPipeline CreateRenderPipeline();

        /**
         * @brief Get the shader path for the post process effect.
         */
        virtual std::string GetShaderPath() = 0;

    public:
        WebGPUPostProcessEffect(const Framework &framework);

        void Initialize() override;


         /**
         * @brief Draw the effect to the destination texture.
         * @param destinationTextureView The destination texture view. In this case it is of type WGPUTextureView.
         * This is a texture to which we want to render, usually the screen texture.
         * But can be any other texture if there are multiple post process effects.
         */
        void Draw(void *destinationTextureView) override;
    };
} // namespace bns

#endif // !BNS_WEBGPU_POST_PROCESS_EFFECT_HPP