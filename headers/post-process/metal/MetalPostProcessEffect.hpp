#ifndef BNS_METAL_POST_PROCESS_EFFECT_HPP

#define BNS_METAL_POST_PROCESS_EFFECT_HPP

#include "post-process/PostProcessEffect.hpp"
#include "textures/metal/MetalTexture2D.hpp"
#include <string>

/**
 * Each effects should at least have a vertex shader and a fragment shader
 * to draw a full screen quad.
 * Input into fragment shader should be a texture and texture coordinates which represent what was drawn so far to screen.
 */

namespace bns
{
    class Framework;

    class MetalPostProcessEffect : public PostProcessEffect
    {
    protected:
        /**
         * The device. Fetched in initialize.
         */
        MTL::Device *m_device;

        MTL::RenderPipelineState *m_pipeline; // post process shaders pipeline
        MTL::Buffer *m_vertexBuffer;     // for screen geometry
        MTL::SamplerState *m_samplerState; // for source texture

        /**
         * @brief Create a vertex buffer for a full screen quad.
         * Buffer is created as an array buffer (no indices).
         * Holds 6 vertices (2 triangles) with 2 floats for position and 2 floats for texture coordinates.
         */
        virtual MTL::Buffer* CreateVertexBuffer();

        /**
         * @brief Create a render pipeline for the post process effect.
         * By default simple pipeline is provided which assumes that it takes a texture and draws it to screen.
         */
        virtual MTL::RenderPipelineState* CreateRenderPipeline();

        /**
         * @brief Get the shader path for the post process effect.
         */
        virtual std::string GetShaderPath() = 0;

    public:
        MetalPostProcessEffect(const Framework &framework);

        void Initialize() override;


         /**
         * @brief Draw the effect to the destination texture.
         * @param destinationTexture The destination texture. In this case it is of type MetalTexture.
         * This is a texture to which we want to render, usually the screen texture.
         * But can be any other texture if there are multiple post process effects.
         */
        void Draw(void *destinationTexture) override;
    };
} // namespace bns

#endif // !BNS_WEBGPU_POST_PROCESS_EFFECT_HPP