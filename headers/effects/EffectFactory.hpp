#ifndef BNS_POST_PROCESS_EFFECT_FACTORY_HPP
#define BNS_POST_PROCESS_EFFECT_FACTORY_HPP

#include "effects/Effect.hpp"
#include "effects/GrayscaleEffect.hpp"
#include "effects/TextureCombineEffect.hpp"
#include "effects/BlurEffect.hpp"
#include "effects/BloomEffect.hpp"

namespace bns
{
    class Framework;

    /**
     * @brief A factory for creating post process effects.
     */
    class EffectFactory final
    {
        private:
        Framework &m_framework;
    public:
        /**
         * @brief Construct a new post process effect factory.
         * @param framework The framework.
        */
        EffectFactory(Framework &framework);

        /**
         * @brief Create a Grayscale post process effect.
         * @return The post process effect.
         */
        GrayscaleEffect *CreateGrayscaleEffect();

        /// @brief Create a Texture Combine post process effect.
        /// @return The post process effect.
        TextureCombineEffect* CreateTextureCombineEffect();

        /// @brief Create a Blur post process effect.
        /// @return The post process effect.
        BlurEffect* CreateBlurEffect();

        /// @brief Create a Bloom post process effect.
        /// @return The post process effect.
        BloomEffect* CreateBloomEffect();
    };
}

#endif
