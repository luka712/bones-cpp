#ifndef BNS_METAL_BLUR_EFFECT_HPP

#define BNS_METAL_BLUR_EFFECT_HPP

#include "post-process/metal/MetalEffectImpl.hpp"
#include "post-process/BlurEffect.hpp"

namespace bns
{
    class Framework;

    class MetalBlurEffectImpl final : public MetalEffectImpl
    {
    private:
        MTL::RenderPipelineState* m_horizontalPassPipeline;
        MTL::RenderPipelineState* m_verticalPassPipeline;

        MetalTexture2D *m_horizontalPassTexture;
        MetalTexture2D *m_verticalPassTexture;

    protected:
        inline std::string GetShaderPath() override
        {
            return "shaders/metal/post-process/blur.metal";
        }

    public:
        MetalBlurEffectImpl(const Framework &framework);

        inline Texture2D *GetSourceTexture() override
        {
            // draw scene into horizontal pass texture, as it is first pass 
            return m_horizontalPassTexture;
        }

        /// @brief Initializes the post process effect.
        void Initialize() override;

        /// @brief Draws the post process effect to the destination texture.
        /// @param destinationTexture - The destination texture. Usually the screen texture.
        void Draw(void *destinationTexture) override;
    };

    class MetalBlurEffect final : public BlurEffect
    {
    private:
        MetalBlurEffectImpl *m_impl;

    public:
        /// @brief The constructor for the blur effect.
        /// @param framework - The framework.
        MetalBlurEffect(const Framework &framework);

        /// @brief Gets the render texture, texture to which effect will render.
        /// @return - The render texture.
        inline Texture2D *GetSourceTexture() override
        {
            return m_impl->GetSourceTexture();
        }

        /// @brief Initializes the effect.
        inline void Initialize() override
        {
            m_impl->Initialize();
        }

        /// @brief Draws the effect to the destination texture.
        /// @param destinationTexture - The destination texture.
        /// This is a texture to which we want to render, usually the screen texture.
        /// But can be any other texture if there are multiple post process effects.
        inline void Draw(void *destinationTexture) override
        {
            m_impl->Draw(destinationTexture);
        }
    };

}

#endif
