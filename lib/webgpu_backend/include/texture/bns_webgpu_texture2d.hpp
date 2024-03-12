#if USE_WEBGPU

#ifndef BNS_WEBGPU_TEXTURE_2D_HPP

#define BNS_WEBGPU_TEXTURE_2D_HPP

#include "renderer/bns_webgpu_renderer.hpp"
#include "texture/bns_texture2d.hpp"
#include "ImageData.hpp"
#include "bns_webgpu.hpp"
#include "bns_webgpu_util.hpp"

namespace bns
{
    class WebGPUTexture2D final : public Texture2D
    {
    private:
        WebGPURenderer *m_renderer;

        /// Temporary image data. To be released by user after texture is initialized.
        ImageData *m_imageData;

        /// @brief Convert the sampler min filter to WebGPU filter mode.
        WGPUFilterMode Convert(SamplerMinFilter minFilter) const;

        /// @brief Convert the sampler mag filter to WebGPU filter mode.
        WGPUFilterMode Convert(SamplerMagFilter magFilter) const;

        /// @brief Create the sampler.
        void CreateSampler();

    public:
        /// @brief The sampler. Exposed so that it can be used by shader, when creating texture bind group.
        WGPUSampler Sampler;

        /// @brief The texture. Exposed so that it can be used by shader, when creating texture bind group.
        WGPUTexture Texture;

        /// @brief The constructor.
        WebGPUTexture2D(Renderer* renderer, ImageData *imageData, TextureUsage textureUsage, TextureFormat format);

        /// @brief The destructor.
        ~WebGPUTexture2D();

        /// @brief Creates the texture view.
        /// @param label The label.
        /// @return The texture view.
        WGPUTextureView CreateView(std::string label = "") const;

        /// @brief Initialize the texture.         
        void Initialize() override;

        /// @brief Destroy the texture.
        void Dispose() override;

        /// @brief Create an empty texture.
        /// @param renderer The renderer.
        /// @param width The width of the texture.
        /// @param height The height of the texture.
        /// @param textureUsage The texture usage. By default, it is CopyDst_TextureBinding.
        /// @return The empty texture.
        static WebGPUTexture2D* CreateEmpty(Renderer* renderer, u32 width, u32 height, TextureUsage textureUsage = TextureUsage::CopyDst_TextureBinding);
    };
}

#endif // !BNS_WEBGPU_TEXTURE_2D_HPP

#endif // USE_WEBGPU