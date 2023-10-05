#ifndef BNS_BLUR_EFFECT_HPP

#define BNS_BLUR_EFFECT_HPP

#include "post-process/Effect.hpp"

namespace bns 
{
    class Framework;

    class BlurEffect : public Effect 
    {
        public:
             /// @brief The constructor for the blur effect.
             /// @param framework - The framework.
             BlurEffect(const Framework &framework);
    };
}

#endif 