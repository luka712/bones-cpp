#if USE_WEBGPU

#ifndef BNS_WEBGPU_POST_PROCESS_TEXTURE_COMBINE_EFFECT_HPP

#define BNS_WEBGPU_POST_PROCESS_TEXTURE_COMBINE_EFFECT_HPP

#include "effects/wgpu/WebGPUEffectImpl.hpp"
#include "effects/TextureCombineEffect.hpp"
#include <math.h>
#include <algorithm>

namespace bns
{
    class WebGPUTextureCombineEffectImpl final : public WebGPUEffectImpl
    {
    private:
        // combine texture data
        WGPUBindGroupLayout m_combineTextureBindGroupLayout; // the bind group layout for the combine texture
        WGPUBindGroup m_combineTextureBindGroup;             // the bind group for the combine texture
        WebGPUTexture2D *m_combineTexture;                   // the combine texture

        // mix value data
        WGPUBindGroupLayout m_mixValueBindGroupLayout; // the bind group layout for the mix value
        WGPUBindGroup m_mixValueBindGroup;             // the bind group for the mix value
        WGPUBuffer m_mixValueBuffer;                   // the mix value buffer
        f32 m_mixValue;                                // the mix value

    protected:
        inline std::string GetShaderPath() override
        {
            return "shaders/webgpu/effects/texture-combine.wgsl";
        }

        /**
         * @brief Create a bind group layouts for the post process effect.
         * By default creates the layout for the source texture.
         * The source texture is the texture which comes into draw.
         * Holds slot 0 for the source texture sampler.
         * Holds slot 1 for the source texture.
         *
         * Creates the layout for the combine texture.
         * The combine texture is the texture which is combined with the source texture in the fragment shader.
         * Holds slot 0 for the combine texture sampler.
         * Holds slot 1 for the combine texture.
         *
         * Creates the layout for the mix value.
         * The mix value is the value which is used to mix the combine texture with the source texture in the fragment shader.
         * Holds slot 0 for the mix value uniform.
         *
         * note
         * m_sourceTextureBindGroupLayout is assigned by default in parent.
         * Override to create additional layouts.
         * Best to override by calling parent method and adding to the result.
         *
         * @return The bind group layout for the post process effect.
         */
        std::vector<WGPUBindGroupLayout> CreateBindGroupLayouts() override;

        /**
         * @brief Create a bind groups.
         * By default it is created for the source texture.
         * The source texture is the texture which comes into draw.
         * Holds slot 0 for the source texture.
         * Holds slot 1 for the source texture sampler.
         *
         * Creates the bind group for the combine texture.
         * The combine texture is the texture which is combined with the source texture in the fragment shader.
         * Holds slot 0 for the combine texture.
         * Holds slot 1 for the combine texture sampler.
         *
         * Creates the layout for the mix value.
         * The mix value is the value which is used to mix the combine texture with the source texture in the fragment shader.
         * Holds slot 0 for the mix value uniform.
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

        /**
         * @brief Creates the bind group for the combine texture.
         * The combine texture is the texture which is combined with the source texture in the fragment shader.
         * Holds slot 0 for the combine texture.
         * Holds slot 1 for the combine texture sampler.
         *
         * Note:
         * m_combineTextureBindGroup is assigned by default in CreateBindGroupLayouts.
         * If combine texture is null, it is ignored and nullptr is returned.
         *
         * @return The bind group for the combine texture. If combine texture is null, it is ignored and nullptr is returned.
         */
        WGPUBindGroup CreateCombineTextureBindGroup();

    public:
        WebGPUTextureCombineEffectImpl(const Framework &framework);

        /**
         * @brief Get the mix value.
         * This is the value which is used to mix the combine texture with the source texture in the fragment shader.
         * The value is clamped between 0 and 1.
         * 0 means that the source(scene) texture is used.
         * 1 means that the combine texture is used.
         * 0.5 means that the textures are mixed equally.
         */
        inline f32 GetMixValue(f32 v)
        {
            return m_mixValue;
        }

        /**
         * @brief Sets the mix value.
         * This is the value which is used to mix the combine texture with the source texture in the fragment shader.
         * The value is clamped between 0 and 1.
         * 0 means that the source(scene) texture is used.
         * 1 means that the combine texture is used.
         * 0.5 means that the textures are mixed equally.
         */
        void SetMixValue(f32 v)
        {
            m_mixValue = std::clamp(v, 0.0f, 1.0f);
        }

        /**
         * @brief Get the combine texture.
         * @return The combine texture.
         * The combine texture is the texture which is combined with the source texture in the fragment shader.
         */
        inline WebGPUTexture2D *GetCombineTexture() const
        {
            return m_combineTexture;
        }

        /**
         * @brief Set the combine texture.
         * @param combineTexture The combine texture.
         * The combine texture is the texture which is combined with the source texture in the fragment shader.
         */
        void SetCombineTexture(WebGPUTexture2D *combineTexture);
        /**
         * @brief Draw the effect to the destination texture.
         * @param destinationTexture The destination texture. In this case it is of type WGPUTextureView.
         * This is a texture to which we want to render, usually the screen texture.
         * But can be any other texture if there are multiple post process effects.
         */
        void Draw(void *destinationTexture) override;
    };

    class WebGPUTextureCombineEffect final : public TextureCombineEffect
    {
    private:
        WebGPUTextureCombineEffectImpl *m_impl;

    public:
        WebGPUTextureCombineEffect(const Framework &framework)
            : TextureCombineEffect(framework)
        {
            m_impl = new WebGPUTextureCombineEffectImpl(framework);
        }

        ~WebGPUTextureCombineEffect()
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

        /**
         * @brief Get the mix value.
         * This is the value which is used to mix the combine texture with the source texture in the fragment shader.
         * The value is clamped between 0 and 1.
         * 0 means that the source(scene) texture is used.
         * 1 means that the combine texture is used.
         * 0.5 means that the textures are mixed equally.
         */
        inline f32 GetMixValue(f32 v) override
        {
            return m_impl->GetMixValue(v);
        }

        /**
         * @brief Sets the mix value.
         * This is the value which is used to mix the combine texture with the source texture in the fragment shader.
         * The value is clamped between 0 and 1.
         * 0 means that the source(scene) texture is used.
         * 1 means that the combine texture is used.
         * 0.5 means that the textures are mixed equally.
         */
        inline void SetMixValue(f32 v) override
        {
            m_impl->SetMixValue(v);
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
        inline Texture2D *GetCombineTexture() const override
        {
            return m_impl->GetCombineTexture();
        }

        /**
         * @brief Set the combine texture.
         * @param combineTexture The combine texture.
         * The combine texture is the texture which is combined with the source texture in the fragment shader.
         */
        inline void SetCombineTexture(Texture2D *combineTexture) override
        {
            m_impl->SetCombineTexture(static_cast<WebGPUTexture2D *>(combineTexture));
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

#endif // !BNS_WEBGPU_POST_PROCESS_TEXTURE_COMBINE_EFFECT_HPP

#endif 