#ifndef BNS_WEBGPU_POST_PROCESS_GRAYSCALE_EFFECT_HPP

#define BNS_WEBGPU_POST_PROCESS_GRAYSCALE_EFFECT_HPP

#include "effects/wgpu/WebGPUEffectImpl.hpp"
#include "effects/GrayscaleEffect.hpp"

namespace bns
{
    /**
     * @brief A WebGPU implementation of a post process effect which converts the source texture to grayscale.
     * This is an implementation.
     * @see GrayscaleEffect
     * @see WebGPUGrayscaleEffect
     * @see WebGPUEffect
     */
    class WebGPUGrayscaleEffectImpl final : public WebGPUEffectImpl
    {
    protected:
        inline std::string GetShaderPath() override
        {
            return "shaders/webgpu/effects/grayscale.wgsl";
        }

    public:
        WebGPUGrayscaleEffectImpl(const Framework &framework);
    };

    /**
     * @brief A WebGPU implementation of a post process effect which converts the source texture to grayscale.
     * This is an interface.
     * @see GrayscaleEffect
     * @see WebGPUGrayscaleEffectImpl
     * @see WebGPUEffect
     */
    class WebGPUGrayscaleEffect final : public GrayscaleEffect
    {
    private:
        WebGPUGrayscaleEffectImpl *m_impl;

    public:
        WebGPUGrayscaleEffect(const Framework &framework)
            : GrayscaleEffect(framework)
        {
            m_impl = new WebGPUGrayscaleEffectImpl(framework);
        }

        Texture2D *GetSourceTexture() override
        {
            return m_impl->GetSourceTexture();
        }

        /// @brief Sets the render texture, texture to which effect will render.
        /// @param texture The render texture
        void SetSourceTexture(Texture2D *texture) override
        {
            m_impl->SetSourceTexture(texture);
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

#endif // !BNS_WEBGPU_POST_PROCESS_GRAYSCALE_EFFECT_HPP