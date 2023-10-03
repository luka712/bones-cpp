#ifndef BNS_METAL_POST_PROCESS_GRAYSCALE_EFFECT_HPP

#define BNS_METAL_POST_PROCESS_GRAYSCALE_EFFECT_HPP

#include "post-process/metal/MetalPostProcessEffect.hpp"
#include "post-process/PostProcessGrayscaleEffect.hpp"

namespace bns
{
    /**
     * @brief A post process effect which converts the source texture to grayscale. This is an implementation.
     * @see PostProcessGrayscaleEffect
     * @see MetalPostProcessGrayscaleEffect
     * @see MetalPostProcessEffect
     */
    class MetalPostProcessGrayscaleEffectImpl final : public MetalPostProcessEffect
    {
    protected:
        inline std::string GetShaderPath() override
        {
            return "shaders/metal/post-process/grayscale.metal";
        }

    public:
        MetalPostProcessGrayscaleEffectImpl(const Framework &framework);
    };

    /**
     * @brief A post process effect which converts the source texture to grayscale. This is an interface.
     * @see PostProcessGrayscaleEffect
     * @see MetalPostProcessGrayscaleEffectImpl
     * @see MetalPostProcessEffect
     */
    class MetalPostProcessGrayscaleEffect final : public PostProcessGrayscaleEffect
    {
    private:
        MetalPostProcessGrayscaleEffectImpl* m_impl;

    public:
        MetalPostProcessGrayscaleEffect( const Framework& m_framework)
            : PostProcessGrayscaleEffect(m_framework)
        {
            m_impl = new MetalPostProcessGrayscaleEffectImpl(m_framework);
        }

        Texture2D* GetSourceTexture() override
        {
            return m_impl->GetSourceTexture();
        }
        
        void Initialize() override
        {
            m_impl->Initialize();
        }

        void Draw(void *destinationTexture) override
        {
            m_impl->Draw(destinationTexture);
        }
    };

} // namespace bns

#endif // !BNS_METAL_POST_PROCESS_GRAYSCALE_EFFECT_HPP
