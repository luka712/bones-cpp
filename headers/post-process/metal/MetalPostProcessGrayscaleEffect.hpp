#ifndef BNS_METAL_POST_PROCESS_GRAYSCALE_EFFECT_HPP

#define BNS_METAL_POST_PROCESS_GRAYSCALE_EFFECT_HPP

#include "post-process/metal/MetalPostProcessEffect.hpp"

namespace bns
{
    class MetalPostProcessGrayscaleEffect final : public MetalPostProcessEffect
    {
    protected:
        inline std::string GetShaderPath() override
        {
            return "shaders/metal/post-process/grayscale.metal";
        }

    public:
        MetalPostProcessGrayscaleEffect(const Framework &framework);
    };
} // namespace bns

#endif // !BNS_METAL_POST_PROCESS_GRAYSCALE_EFFECT_HPP