#ifndef BNS_POST_PROCESS_GRAYSCALE_EFFECT_HPP
#define BNS_POST_PROCESS_GRAYSCALE_EFFECT_HPP

#include "post-process/PostProcessEffect.hpp"

namespace bns 
{

    /**
     * @brief A post process effect which converts the source texture to grayscale. This is an interface.
    */
    class PostProcessGrayscaleEffect : public PostProcessEffect
    {
        public:
            PostProcessGrayscaleEffect(const Framework &framework);
    };
}

#endif 