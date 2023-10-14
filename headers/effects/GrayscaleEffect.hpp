#ifndef BNS_POST_PROCESS_GRAYSCALE_EFFECT_HPP
#define BNS_POST_PROCESS_GRAYSCALE_EFFECT_HPP

#include "effects/Effect.hpp"

namespace bns 
{

    /**
     * @brief A post process effect which converts the source texture to grayscale. This is an interface.
    */
    class GrayscaleEffect : public Effect
    {
        public:
            GrayscaleEffect(const Framework &framework);
    };
}

#endif 