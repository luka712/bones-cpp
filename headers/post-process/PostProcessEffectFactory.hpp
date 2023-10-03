#ifndef BNS_POST_PROCESS_EFFECT_FACTORY_HPP
#define BNS_POST_PROCESS_EFFECT_FACTORY_HPP

#include "post-process/PostProcessEffect.hpp"
#include "post-process/PostProcessGrayscaleEffect.hpp"

namespace bns
{
    class Framework;

    /**
     * @brief A factory for creating post process effects.
     */
    class PostProcessEffectFactory final
    {
    private:
        Framework &m_framework;

    public:
        /**
         * @brief Construct a new post process effect factory.
         * @param framework The framework.
        */
        PostProcessEffectFactory(Framework &framework);

        /**
         * @brief Create a Grayscale post process effect.
         * @param framework The framework.
         * @param name The name of the post process effect.
         * @return The post process effect.
         */
        PostProcessGrayscaleEffect *CreateGrayscaleEffect();
    };
}

#endif