#ifndef BNS_BLOOM_EFFECT_HPP

#define BNS_BLOOM_EFFECT_HPP

#include "effects/Effect.hpp"

namespace bns
{
    class BloomEffect : public Effect
    {
    public:
        /// @brief The constructor for the bloom effect.
        /// @param framework - The framework.
        BloomEffect(const Framework &framework);

        /// @brief Gets the brightness texture. That is texture that will be blurred.
        /// @return The brightness texture.
        virtual Texture2D *GetBrightnessTexture() const = 0;

        /// @brief Sets the brightness texture. That is texture that will be blurred.
        /// @param brightTexture The brightness texture.
        virtual void SetBrightnessTexture(Texture2D *brightTexture) = 0;
    };
}

#endif