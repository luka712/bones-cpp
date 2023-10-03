#include "post-process/PostProcessEffectFactory.hpp"

#if __APPLE__ && USE_METAL
#include "post-process/metal/MetalPostProcessGrayscaleEffect.hpp"
#else
#include "post-process/wgpu/WebGPUPostProcessGrayscaleEffect.hpp"
#endif

namespace bns
{
    PostProcessEffectFactory::PostProcessEffectFactory(Framework &framework) : m_framework(framework)
    {
    }

    PostProcessGrayscaleEffect *PostProcessEffectFactory::CreateGrayscaleEffect()
    {
        PostProcessGrayscaleEffect* effect = nullptr;
#if __APPLE__ && USE_METAL
        effect = new MetalPostProcessGrayscaleEffect(m_framework);
#else
        effect = new WebGPUPostProcessGrayscaleEffect(m_framework);
#endif

        effect->Initialize();
        return effect;
    }
}