#ifndef BNS_METAL_POST_PROCESS_TEXTURE_COMBINE_EFFECT_HPP

#define BNS_METAL_POST_PROCESS_TEXTURE_COMBINE_EFFECT_HPP

#include "post-process/metal/MetalPostProcessEffect.hpp"
#include <math.h>

namespace bns
{
    class MetalPostProcessTextureCombineEffect final : public MetalPostProcessEffect
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
            return "shaders/metal/post-process/texture-combine.metal";
        }

    public:
        MetalPostProcessTextureCombineEffect(const Framework &framework);

        /**
         * @brief Initialize the post process effect.
         */
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
        void SetMixValue(f32 v)
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
} // namespace bns

#endif // !BNS_WEBGPU_POST_PROCESS_TEXTURE_COMBINE_EFFECT_HPP