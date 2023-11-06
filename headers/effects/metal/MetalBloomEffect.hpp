#ifndef BNS_METAL_POST_PROCESS_BLOOM_EFFECT_HPP

#define BNS_METAL_POST_PROCESS_BLOOM_EFFECT_HPP

#include "effects/metal/MetalEffectImpl.hpp"
#include "effects/BloomEffect.hpp"
#include "effects/metal/MetalBlurEffect.hpp"
#include <math.h>
#include "renderer/MetalRenderer.hpp"

namespace bns
{
    class MetalBloomEffectImpl final : public MetalEffectImpl
    {
    private:
        MTL::Device* m_device;

        /// @brief The brightness texture.
        MetalTexture2D *m_brightnessTexture;

        MetalBlurEffect m_blurEffect;

    protected:
        inline std::string GetShaderPath() override
        {
            return "shaders/metal/effects/bloom.metal";
        }

    public:

        u32 BrightnessBlurPasses;

        MetalBloomEffectImpl(const Framework &framework);

        /// @brief Initialize the post process effect.
        void Initialize() override;

        /// @brief Gets the brighntess texture.
        inline MetalTexture2D *GetBrightnessTexture() const
        {
            return m_brightnessTexture;
        }

        /// @brief Sets the brightness texture.
        inline void SetBrightnessTexture(MetalTexture2D *combineTexture)
        {
            m_brightnessTexture = combineTexture;
        }

        /**
         * @brief Draw the effect to the destination texture.
         * @param destinationTexture The destination texture. In this case it is of type WGPUTextureView.
         * This is a texture to which we want to render, usually the screen texture.
         * But can be any other texture if there are multiple post process effects.
         */
        void Draw(void *destinationTexture) override;
    };

    class MetalBloomEffect final : public BloomEffect
    {
    private:
        MetalBloomEffectImpl *m_impl;

    public:
        MetalBloomEffect(const Framework &framework)
            : BloomEffect(framework)
        {
            m_impl = new MetalBloomEffectImpl(framework);
        }

        ~MetalBloomEffect()
        {
            delete m_impl;
        }

        /**
         * @brief Initialize the post process effect.
         */
        inline void Initialize() override
        {
            m_impl->Initialize();
        }

        /// @brief Gets the source texture.
        /// @return The source texture.
        inline Texture2D *GetSourceTexture() override
        {
            return m_impl->GetSourceTexture();
        }

        /// @brief Sets the render texture, texture to which effect will render.
        /// @param texture The render texture
        inline void SetSourceTexture(Texture2D *texture) override
        {
            m_impl->SetSourceTexture(texture);
        }

        /**
         * @brief Get the combine texture.
         * @return The combine texture.
         * The combine texture is the texture which is combined with the source texture in the fragment shader.
         */
        inline Texture2D *GetBrightnessTexture() const override
        {
            return m_impl->GetBrightnessTexture();
        }

        /**
         * @brief Set the combine texture.
         * @param brightnessTexture The combine texture.
         * The combine texture is the texture which is combined with the source texture in the fragment shader.
         */
        inline void SetBrightnessTexture(Texture2D *brightnessTexture) override
        {
            m_impl->SetBrightnessTexture(static_cast<MetalTexture2D *>(brightnessTexture));
        }

        /**
         * @brief Draw the effect to the destination texture.
         * @param destinationTexture The destination texture. In this case it is of type WGPUTextureView.
         * This is a texture to which we want to render, usually the screen texture.
         * But can be any other texture if there are multiple post process effects.
         */
        inline void Draw(void *destinationTexture) override
        {
            m_impl->Draw(destinationTexture);
        }
    };
} // namespace bns

#endif // !BNS_WEBGPU_POST_PROCESS_BLOOM_EFFECT_HPP
