#include "post-process/EffectFactory.hpp"

#if __APPLE__ && USE_METAL
#include "post-process/metal/MetalGrayscaleEffect.hpp"
#include "post-process/metal/MetalTextureCombineEffect.hpp"
#include "post-process/metal/MetalBlurEffect.hpp"
#else
#include "post-process/wgpu/WebGPUGrayscaleEffect.hpp"
#include "post-process/wgpu/WebGPUTextureCombineEffect.hpp"
#include "post-process/wgpu/WebGPUBlurEffect.hpp"
#endif

namespace bns
{
        EffectFactory::EffectFactory(Framework &framework) : m_framework(framework)
        {
        }

        GrayscaleEffect *EffectFactory::CreateGrayscaleEffect()
        {
                GrayscaleEffect *effect = nullptr;
#if __APPLE__ && USE_METAL
                effect = new MetalGrayscaleEffect(m_framework);
#else
                effect = new WebGPUGrayscaleEffect(m_framework);
#endif

                effect->Initialize();
                return effect;
        }

        TextureCombineEffect *EffectFactory::CreateTextureCombineEffect()
        {
                TextureCombineEffect *effect = nullptr;
#if __APPLE__ && USE_METAL
                effect = new MetalTextureCombineEffect(m_framework);
#else
                effect = new WebGPUTextureCombineEffect(m_framework);
#endif

                effect->Initialize();
                return effect;
        }

        BlurEffect *EffectFactory::CreateBlurEffect()
        {
                BlurEffect *effect = nullptr;
#if __APPLE__ && USE_METAL
                effect = new MetalBlurEffect(m_framework);
#else
                effect = new WebGPUBlurEffect(m_framework);
#endif

                effect->Initialize();
                return effect;
        }
}