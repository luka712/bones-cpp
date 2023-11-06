#ifdef __APPLE__

#ifndef BNS_METAL_POST_PROCESS_EFFECT_HPP

#define BNS_METAL_POST_PROCESS_EFFECT_HPP

#include "effects/Effect.hpp"
#include "texture/MetalTexture2D.hpp"
#include <string>
#include "renderer/MetalRenderer.hpp"


/**
 * Each effects should at least have a vertex shader and a fragment shader
 * to draw a full screen quad.
 * Input into fragment shader should be a texture and texture coordinates which represent what was drawn so far to screen.
 */

namespace bns
{
    class Framework;

    class MetalEffectImpl : public Effect
    {
    protected:
        /// @brief The renderer.
        MetalRenderer *m_renderer;

        /// @brief The device.
        MTL::Device *m_device;

        MTL::RenderPipelineState *m_pipeline; // post process shaders pipeline
        MTL::Buffer *m_vertexBuffer;          // for screen geometry

        /**
         * @brief The source texture.
         * This is the texture that we want to apply the effect to.
         */
        Texture2D *m_sourceTexture = nullptr;

        /**
         * @brief Create a vertex buffer for a full screen quad.
         * Buffer is created as an array buffer (no indices).
         * Holds 6 vertices (2 triangles) with 2 floats for position and 2 floats for texture coordinates.
         */
        virtual MTL::Buffer *CreateVertexBuffer();

        
        /// @brief Create a render pipeline for the post process effect.
        /// By default simple pipeline is provided which assumes that it takes a texture and draws it to screen.
        /// @note @ref m_pipeline is set to the result of this method.
        virtual MTL::RenderPipelineState *CreateRenderPipeline();

        /// @brief Creates a render pipeline for the post process effect. By default simply pipeline is provided, nothing is set internally.
        /// @param pLibrary The library which contains the vertex and fragment functions.
        /// @param vertexFunctionName The name of the vertex function. Usually "vs_main".
        /// @param fragmentFunctionName The name of the fragment function Usually "fs_main".
        /// @param pixelFormat The pixel format of the render pipeline. By default MTL::PixelFormat::PixelFormatBGRA8Unorm.
        /// @return The render pipeline for the post process effect.
        /// @note @ref CreateRenderPipeline as it is caller of this method.
        virtual MTL::RenderPipelineState *CreateRenderPipeline(MTL::Library* pLibrary,
         std::string vertexFunctionName = "vs_main", 
         std::string fragmentFunctionName = "fs_main",
         MTL::PixelFormat pixelFormat =  MTL::PixelFormat::PixelFormatBGRA8Unorm);

        /**
         * @brief Get the shader path for the post process effect.
         */
        virtual std::string GetShaderPath() = 0;

    public:
        MetalEffectImpl(const Framework &framework);

        void Initialize() override;

        /**
         * @brief Get the source texture.
         * @return The source texture.
         * This is the texture that we want to apply the effect to.
         */
        inline Texture2D *GetSourceTexture() override
        {
            return m_sourceTexture;
        }

        /// @brief Sets the source texture.
        /// @param sourceTexture The source texture.
        /// This is the texture that we want to apply the effect to.
        inline void SetSourceTexture(Texture2D* sourceTexture) override
        {
            m_sourceTexture = sourceTexture;
        }

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

#endif // __APPLE__