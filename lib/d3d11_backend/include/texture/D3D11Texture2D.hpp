#if USE_D3D11

#ifndef BNS_D3D11_TEXTURE_2D_HPP

#define BNS_D3D11_TEXTURE_2D_HPP

#include "texture/Texture2D.hpp"
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
        D3D11Texture2D(CComPtr<ID3D11Device> device, ImageData *imageData, i32 textureUsageFlags, TextureFormat format);

        /// @brief The destructor.
        ~D3D11Texture2D();

        /// @brief Initialize the texture.
        void Initialize() override;

        /// @brief Release the texture.
        void Release() override;
    };
}

#endif // !BNS_D3D11_TEXTURE_2D_HPP

#endif // D3D11