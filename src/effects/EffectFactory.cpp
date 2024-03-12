#include "effects/EffectFactory.hpp"
#include "bns_framework.hpp"

#if __APPLE__ && USE_METAL
#include "effects/metal/MetalGrayscaleEffect.hpp"
#include "effects/metal/MetalTextureCombineEffect.hpp"
#include "effects/metal/MetalBlurEffect.hpp"
#include "effects/metal/MetalBloomEffect.hpp"
#endif 

#if USE_WEBGPU
#include "effects/wgpu/WebGPUGrayscaleEffect.hpp"
#include "effects/wgpu/WebGPUTextureCombineEffect.hpp"
#include "effects/wgpu/WebGPUBlurEffect.hpp"
#include "effects/wgpu/WebGPUBloomEffect.hpp"
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
#elif USE_WEBGPU
                effect = new WebGPUGrayscaleEffect(m_framework);
#endif
            m_framework.GetFileLoader();
                effect->Initialize();
                return effect;
        }

        TextureCombineEffect *EffectFactory::CreateTextureCombineEffect()
        {
                TextureCombineEffect *effect = nullptr;
#if __APPLE__ && USE_METAL
                effect = new MetalTextureCombineEffect(m_framework);
#elif USE_WEBGPU
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
#elif USE_WEBGPU
                effect = new WebGPUBlurEffect(m_framework);
#endif

                effect->Initialize();
                return effect;
        }

        BloomEffect *EffectFactory::CreateBloomEffect()
        {
                BloomEffect *effect = nullptr;
#if __APPLE__ && USE_METAL
                effect = new MetalBloomEffect(m_framework);
#elif USE_WEBGPU
                effect = new WebGPUBloomEffect(m_framework);
#endif

                effect->Initialize();
                return effect;
        }
}
