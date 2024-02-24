#ifndef BNS_POST_PROCESS_TEXURE_COMBINE_EFFECT_HPP
#define BNS_POST_PROCESS_TEXURE_COMBINE_EFFECT_HPP

#include "effects/Effect.hpp"
#include "texture/bns_texture2d.hpp"

namespace bns
{

    /**
     * @brief A post process effect which combines render texture (usually, but can be other) with given texture.
     * This is an interface.
     */
    class TextureCombineEffect : public Effect
    {
    public:
        inline TextureCombineEffect(const Framework &framework)
            : Effect(framework)
        {
        }

        /**
         * @brief Get the mix value.
         * This is the value which is used to mix the combine texture with the source texture in the fragment shader.
         * The value is clamped between 0 and 1.
         * 0 means that the source(scene) texture is used.
         * 1 means that the combine texture is used.
         * 0.5 means that the textures are mixed equally.
         */
        virtual f32 GetMixValue(f32 v) = 0;

        /**
         * @brief Sets the mix value.
         * This is the value which is used to mix the combine texture with the source texture in the fragment shader.
         * The value is clamped between 0 and 1.
         * 0 means that the source(scene) texture is used.
         * 1 means that the combine texture is used.
         * 0.5 means that the textures are mixed equally.
         */
        virtual void SetMixValue(f32 v) = 0;

        /**
         * @brief Get the combine texture.
         * @return The combine texture.
         * The combine texture is the texture which is combined with the source texture in the fragment shader.
         */
        virtual Texture2D *GetCombineTexture() const = 0;

        /**
         * @brief Set the combine texture.
         * @param combineTexture The combine texture.
         * The combine texture is the texture which is combined with the source texture in the fragment shader.
         */
        virtual void SetCombineTexture(Texture2D *combineTexture) = 0;
    };
}

#endif