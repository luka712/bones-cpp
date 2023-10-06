#ifndef BNS_WEBGPU_BLUR_EFFECT_HPP

#define BNS_WEBGPU_BLUR_EFFECT_HPP

#include "post-process/wgpu/WebGPUEffectImpl.hpp"
#include "post-process/BlurEffect.hpp"

namespace bns
{
    class Framework;

    class WebGPUBlurEffectImpl final : public WebGPUEffectImpl
    {
    private:
        WGPURenderPipeline m_horizontalPassPipeline;
        WGPURenderPipeline m_verticalPassPipeline;

        WebGPUTexture2D *m_horizontalPassTexture;
        WebGPUTexture2D *m_verticalPassTexture;

        WGPUBindGroup m_horizontalPassTextureBindGroup;
        WGPUBindGroup m_verticalPassTextureBindGroup;

        /// @brief Create a render pipeline for the post process effect.
        /// @param shaderModule - The shader module. This is module created from blur.wgsl
        /// @param bindGroupLayout - The bind group layout. One of m_horizontalPassTextureBindGroupLayout or m_verticalPassTextureBindGroupLayout.
        /// @param fragmentMainName - The name of the fragment shader main function. One of fs_main_horizontal_pass or fs_main_vertical_pass.
        /// @return The render pipeline for the post process effect.
        WGPURenderPipeline CreatePipeline(WGPUShaderModule shaderModule, WGPUBindGroupLayout bindGroupLayout, std::string& fragmentMainName);

    protected:
        inline std::string GetShaderPath() override
        {
            return "shaders/webgpu/post-process/blur.wgsl";
        }

        /// @brief Creates the bind groups for the post process effect.
        /// @return - The bind groups for the post process effect.
        /// Here it is overriden in order to create the bind groups for the horizontal and vertical pass textures.
        std::vector<WGPUBindGroup> CreateBindGroups(std::vector<WGPUBindGroupLayout> bindGroupLayouts) override;

        /// @brief Create a render pipeline for the post process effect.
        /// By default simple pipeline is provided which assumes that it takes a texture and draws it to screen.
        /// @param bindGroupLayouts The bind group layouts created by CreateBindGroupLayouts.
        /// This will internally set m_horizontalPassPipeline and m_verticalPassPipeline. Do not use return result, it is set to nullptr.
        WGPURenderPipeline CreateRenderPipeline(std::vector<WGPUBindGroupLayout> bindGroupLayouts) override;

    public:
        WebGPUBlurEffectImpl(const Framework &framework);

        inline Texture2D *GetSourceTexture() override
        {
            // draw scene into horizontal pass texture as it is first pass
            return m_horizontalPassTexture;
        }

        /// @brief Initializes the post process effect.
        void Initialize() override;

        /// @brief Draws the post process effect to the destination texture.
        /// @param destinationTexture - The destination texture. Usually the screen texture.
        void Draw(void *destinationTexture) override;
    };

    class WebGPUBlurEffect final : public BlurEffect
    {
    private:
        WebGPUBlurEffectImpl *m_impl;

    public:
        /// @brief The constructor for the blur effect.
        /// @param framework - The framework.
        WebGPUBlurEffect(const Framework &framework)
            : BlurEffect(framework)
        {
            m_impl = new WebGPUBlurEffectImpl(framework);
        }

        /// @brief Gets the render texture, texture to which effect will render.
        /// @return - The render texture.
        Texture2D *GetSourceTexture() override
        {
            return m_impl->GetSourceTexture();
        }

        /// @brief Initializes the effect.
        void Initialize() override
        {
            m_impl->Initialize();
        }

        /// @brief Draws the effect to the destination texture.
        /// @param destinationTexture - The destination texture.
        /// This is a texture to which we want to render, usually the screen texture.
        /// But can be any other texture if there are multiple post process effects.
        void Draw(void *destinationTexture) override
        {
            m_impl->Draw(destinationTexture);
        }
    };

}

#endif
