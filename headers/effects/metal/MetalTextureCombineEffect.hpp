#ifndef BNS_METAL_POST_PROCESS_TEXTURE_COMBINE_EFFECT_HPP

#define BNS_METAL_POST_PROCESS_TEXTURE_COMBINE_EFFECT_HPP

#include "effects/metal/MetalEffectImpl.hpp"
#include "effects/TextureCombineEffect.hpp"
#include <math.h>

namespace bns
{
    class MetalTextureCombineEffectImpl final : public MetalEffectImpl
    {
    private:
        // combine texture data
        MetalTexture2D *m_combineTexture; // the combine texture

        // Mix value
        MTL::Buffer *m_mixValueBuffer;
        float m_mixValue;

    protected:
        inline std::string GetShaderPath() override
        {
            return "shaders/metal/effects/texture-combine.metal";
        }

    public:
        MetalTextureCombineEffectImpl(const Framework &framework);

        /// @brief Initialize the post process effect.
        void Initialize() override;

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
        inline void SetMixValue(f32 v)
        {
            m_mixValue = std::clamp(v, 0.0f, 1.0f);
        }

        /**
         * @brief Get the combine texture.
         * @return The combine texture.
         * The combine texture is the texture which is combined with the source texture in the fragment shader.
         */
        inline MetalTexture2D *GetCombineTexture() const
        {
            return m_combineTexture;
        }

        /**
         * @brief Set the combine texture.
         * @param combineTexture The combine texture.
         * The combine texture is the texture which is combined with the source texture in the fragment shader.
         */
        inline void SetCombineTexture(MetalTexture2D *combineTexture)
        {
            m_combineTexture = combineTexture;
        }

        /**
         * @brief Draw the effect to the destination texture.
         * @param destinationTexture The destination texture. In this case it is of type WGPUTextureView.
         * This is a texture to which we want to render, usually the screen texture.
         * But can be any other texture if there are multiple post process effects.
         */
        void Draw(void *destinationTexture) override;
    };

    class MetalTextureCombineEffect final : public TextureCombineEffect
    {
    private:
        MetalTextureCombineEffectImpl *m_impl;

    public:
         MetalTextureCombineEffect(const Framework &framework)
            : TextureCombineEffect(framework)
        {
            m_impl = new MetalTextureCombineEffectImpl(framework);
        }

         ~MetalTextureCombineEffect()
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
            m_impl->SetCombineTexture(static_cast<MetalTexture2D *>(combineTexture));
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
