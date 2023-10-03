#ifndef BNS_WEBGPU_POST_PROCESS_GRAYSCALE_EFFECT_HPP

#define BNS_WEBGPU_POST_PROCESS_GRAYSCALE_EFFECT_HPP

#include "post-process/wgpu/WebGPUPostProcessEffect.hpp"
#include "post-process/PostProcessGrayscaleEffect.hpp"

namespace bns
{
    /**
     * @brief A WebGPU implementation of a post process effect which converts the source texture to grayscale.
     * This is an implementation.
     * @see PostProcessGrayscaleEffect
     * @see WebGPUPostProcessGrayscaleEffect
     * @see WebGPUPostProcessEffect
     */
    class WebGPUPostProcessGrayscaleEffectImpl final : public WebGPUPostProcessEffect
    {
    protected:
        inline std::string GetShaderPath() override
        {
            return "shaders/webgpu/post-process/grayscale.wgsl";
        }

    public:
        WebGPUPostProcessGrayscaleEffectImpl(const Framework &framework);
    };

    /**
     * @brief A WebGPU implementation of a post process effect which converts the source texture to grayscale.
     * This is an interface.
     * @see PostProcessGrayscaleEffect
     * @see WebGPUPostProcessGrayscaleEffectImpl
     * @see WebGPUPostProcessEffect
     */
    class WebGPUPostProcessGrayscaleEffect final : public PostProcessGrayscaleEffect
    {
    private:
        WebGPUPostProcessGrayscaleEffectImpl *m_impl;

    public:
        WebGPUPostProcessGrayscaleEffect(const Framework &framework)
            : PostProcessGrayscaleEffect(framework)
        {
            m_impl = new WebGPUPostProcessGrayscaleEffectImpl(framework);
        }

        Texture2D *GetSourceTexture() override
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

#endif // !BNS_WEBGPU_POST_PROCESS_GRAYSCALE_EFFECT_HPP