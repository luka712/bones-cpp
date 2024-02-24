#if USE_D3D11

#ifndef BNS_D3D11_TEXTURE_2D_HPP

#define BNS_D3D11_TEXTURE_2D_HPP

#include "texture/bns_texture2d.hpp"
#include "ImageData.hpp"
#include "BnsDirectX11.hpp"

namespace bns
{
    /// @brief The D3D11 texture 2D.
    class D3D11Texture2D final : public Texture2D
    {
    private:
        /// @brief The device.
        CComPtr<ID3D11Device> m_device;

        /// @brief Temporary image data. To be released by user after texture is initialized.
        ImageData *m_imageData;

        /// @brief Convert the texture format to D3D11 texture format.
        DXGI_FORMAT Convert(TextureFormat format);

        /// @brief Convert the texture usage flags to D3D11 texture usage flags.
        UINT Convert(i32 textureUsageFlags);

        /// @brief Convert the min filter and mag filter to D3D11 filter.
        /// @param minFilter The min filter.
        /// @param magFilter The mag filter.
        /// @return The D3D11 filter.
        D3D11_FILTER Convert(SamplerMinFilter minFilter, SamplerMagFilter magFilter);

    public:
        /// @brief The D3D11 sampler state.
        CComPtr<ID3D11SamplerState> Sampler;

        /// @brief The D3D11 texture.
        CComPtr<ID3D11Texture2D> Texture;

        /// @brief The D3D11 texture view.
        CComPtr<ID3D11ShaderResourceView> TextureView;

        /// @brief The constructor.
        /// @param device The device.
        /// @param imageData The image data.
        /// @param textureUsageFlags The texture usage flags.
        /// @param format The texture format.
        /// @param minFilter The min filter. By default, it is set to SamplerMinFilter::LINEAR.
        /// @param magFilter The mag filter. By default, it is set to SamplerMagFilter::LINEAR.
        D3D11Texture2D(CComPtr<ID3D11Device> device, ImageData *imageData, i32 textureUsageFlags, TextureFormat format,
                       SamplerMinFilter minFilter = SamplerMinFilter::LINEAR,
                       SamplerMagFilter magFilter = SamplerMagFilter::LINEAR);

        /// @brief The destructor.
        ~D3D11Texture2D();

        /// @brief Initialize the texture.
        void Initialize() override;

        /// @brief Release the texture.
        void Dispose() override;
    };
}

#endif // !BNS_D3D11_TEXTURE_2D_HPP

#endif // D3D11