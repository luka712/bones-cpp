#ifndef BNS_METAL_POST_PROCESS_GRAYSCALE_EFFECT_HPP

#define BNS_METAL_POST_PROCESS_GRAYSCALE_EFFECT_HPP

#include "effects/metal/MetalEffectImpl.hpp"
#include "effects/GrayscaleEffect.hpp"

namespace bns
{
    /**
     * @brief A post process effect which converts the source texture to grayscale. This is an implementation.
     * @see GrayscaleEffect
     * @see MetalGrayscaleEffect
     * @see MetalEffectImpl
     */
    class MetalGrayscaleEffectImpl final : public MetalEffectImpl
    {
    protected:
        inline std::string GetShaderPath() override
        {
            return "shaders/metal/effects/grayscale.metal";
        }

    public:
        /// @brief Construct a new Metal Grayscale Effect Impl object.
        /// @param framework - The framework.
        MetalGrayscaleEffectImpl(const Framework &framework);
    };

    /**
     * @brief A post process effect which converts the source texture to grayscale. This is an interface.
     * @see GrayscaleEffect
     * @see MetalGrayscaleEffectImpl
     * @see MetalEffectImpl
     */
    class MetalGrayscaleEffect final : public GrayscaleEffect
    {
    private:
        MetalGrayscaleEffectImpl *m_impl;

    public:
        inline MetalGrayscaleEffect(const Framework &m_framework)
            : GrayscaleEffect(m_framework)
        {
            m_impl = new MetalGrayscaleEffectImpl(m_framework);
        }

        inline ~MetalGrayscaleEffect()
        {
            delete m_impl;
        }

        inline Texture2D *GetSourceTexture() override
        {
            return m_impl->GetSourceTexture();
        }

        inline void Initialize() override
        {
            m_impl->Initialize();
        }

        inline void Draw(void *destinationTexture) override
        {
            m_impl->Draw(destinationTexture);
        }
    };

} // namespace bns

#endif // !BNS_METAL_POST_PROCESS_GRAYSCALE_EFFECT_HPP
