#ifndef BNS_WEBGPU_POST_PROCESS_GRAYSCALE_EFFECT_HPP

#define BNS_WEBGPU_POST_PROCESS_GRAYSCALE_EFFECT_HPP

#include "post-process/wgpu/WebGPUPostProcessEffect.hpp"

namespace bns
{
    class WebGPUPostProcessGrayscaleEffect final : public WebGPUPostProcessEffect
    {
    protected:
        inline std::string GetShaderPath() override
        {
            return "shaders/webgpu/post-process/grayscale.wgsl";
        }

    public:
        WebGPUPostProcessGrayscaleEffect(const Framework &framework);
    };
} // namespace bns

#endif // !BNS_WEBGPU_POST_PROCESS_GRAYSCALE_EFFECT_HPP