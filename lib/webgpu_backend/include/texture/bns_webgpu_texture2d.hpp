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

        /// @brief Convert the texture usage flags to WebGPU texture usage flags.
        WGPUTextureUsage Convert(TextureUsage textureUsage) const;

        /// @brief Convert the texture format to WebGPU texture format.
        WGPUTextureFormat Convert(TextureFormat format) const;

        /// @brief Convert the sampler min filter to WebGPU filter mode.
        WGPUFilterMode Convert(SamplerMinFilter minFilter) const;

        /// @brief Convert the sampler mag filter to WebGPU filter mode.
        WGPUFilterMode Convert(SamplerMagFilter magFilter) const;

        /// @brief Create the texture.
        void CreateTexture();

        /// @brief Write to the texture.
        void WriteToTexture();

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
        /// @return The texture view.
        WGPUTextureView CreateView() const;

        /// @brief Initialize the texture.         
        void Initialize() override;

        /// @brief Destroy the texture.
        void Dispose() override;
    };
}

#endif // !BNS_WEBGPU_TEXTURE_2D_HPP

#endif // USE_WEBGPU