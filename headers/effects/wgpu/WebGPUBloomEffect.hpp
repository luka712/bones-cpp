#ifndef BNS_WEBGPU_BLOOM_EFFECT_HPP

#define BNS_WEBGPU_BLOOM_EFFECT_HPP

#include "effects/wgpu/WebGPUEffectImpl.hpp"
#include "effects/BloomEffect.hpp"
#include "effects/wgpu/WebGPUBlurEffect.hpp"
#include <math.h>

namespace bns
{
    class WebGPUBloomEffectImpl final : public WebGPUEffectImpl
    {
    private:
        WGPUBindGroup m_brightnessTextureBindGroup; // the bind group for the combine texture
        WebGPUTexture2D *m_brightnessTexture;       // the combine texture

        WebGPUBlurEffect m_blurEffect;

    protected:
        inline std::string GetShaderPath() override
        {
            return "shaders/webgpu/effects/bloom.wgsl";
        }

        /**
         * @brief Create a bind groups.
         * By default it is created for the source(screen) texture.
         * The source texture is the texture which comes into draw.
         * Holds slot 0 for the source texture.
         * Holds slot 1 for the source texture sampler.
         *
         * Creates the bind group for the brightness texture.
         * The combine texture is the texture which is combined with the source texture in the fragment shader.
         * Holds slot 0 for the combine texture.
         * Holds slot 1 for the combine texture sampler.
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
        std::vector<WGPUBindGroup> CreateBindGroups(std::vector<WGPUBindGroupLayout> bindGroupLayouts) override;

        /// @brief Create the render pipeline.
        /// @param layouts ignored.
        WGPURenderPipeline CreateRenderPipeline(std::vector<WGPUBindGroupLayout> layouts) override;

        /**
         * @brief Creates the bind group for the brightness texture.
         * The brightness texture is the texture which is combined with the source texture in the fragment shader.
         * Holds slot 0 for the combine texture.
         * Holds slot 1 for the combine texture sampler.
         *
         * Note:
         * m_brightnessTextureBindGroup is assigned by default in CreateBindGroupLayouts.
         * If combine texture is null, it is ignored and nullptr is returned.
         *
         * @return The bind group for the combine texture. If combine texture is null, it is ignored and nullptr is returned.
         */
        WGPUBindGroup CreateBrightnessTextureBindGroup();

    public:
        u32 BrightnessBlurPasses;

        WebGPUBloomEffectImpl(const Framework &framework);

        /// @brief Initializes the post process effect.
        void Initialize() override;

        /// @brief Gets the brighntess texture.
        inline WebGPUTexture2D *GetBrightnessTexture() const
        {
            return m_brightnessTexture;
        }

        /// @brief Sets the brightness texture.
        void SetBrightnessTexture(WebGPUTexture2D *brightnessTexture);

        /**
         * @brief Draw the effect to the destination texture.
         * @param destinationTexture The destination texture. In this case it is of type WGPUTextureView.
         * This is a texture to which we want to render, usually the screen texture.
         * But can be any other texture if there are multiple post process effects.
         */
        void Draw(void *destinationTexture) override;
    };

    class WebGPUBloomEffect final : public BloomEffect
    {
    private:
        WebGPUBloomEffectImpl *m_impl;

    public:
        WebGPUBloomEffect(const Framework &framework)
            : BloomEffect(framework)
        {
            m_impl = new WebGPUBloomEffectImpl(framework);
        }

        ~WebGPUBloomEffect()
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

        /// @brief Sets the source texture.
        /// @param texture The source texture.
        inline void SetSourceTexture(Texture2D* texture) override 
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
            m_impl->SetBrightnessTexture(static_cast<WebGPUTexture2D *>(brightnessTexture));
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

#endif // !BNS_WEBGPU_BLOOM_EFFECT_HPP
