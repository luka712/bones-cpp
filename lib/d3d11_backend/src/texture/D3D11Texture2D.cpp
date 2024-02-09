#if USE_D3D11
#include "texture/D3D11Texture2D.hpp"
#include <stdexcept>
#include <string>
#include "bns_types.hpp"

namespace bns
{
    D3D11Texture2D::D3D11Texture2D(CComPtr<ID3D11Device> device, ImageData *imageData, i32 textureUsageFlags, TextureFormat format,
                                   SamplerMinFilter minFilter,
                                   SamplerMagFilter magFilter)
        : Texture2D(imageData->Width, imageData->Height, textureUsageFlags, format, minFilter, magFilter), m_device(device), m_imageData(imageData)
    {
    }

    D3D11Texture2D::~D3D11Texture2D()
    {
        Release();
    }

    DXGI_FORMAT D3D11Texture2D::Convert(TextureFormat format)
    {
        switch (format)
        {
        case TextureFormat::RGBA_8_Unorm:
            return DXGI_FORMAT_R8G8B8A8_UNORM;
        case TextureFormat::BGRA_8_Unorm:
            return DXGI_FORMAT_B8G8R8A8_UNORM;
        default:
            throw new std::runtime_error("D3D11Texture2D::Convert: Unknown texture format.");
        }
    }

    UINT D3D11Texture2D::Convert(i32 textureUsageFlags)
    {
        UINT bindFlags = 0;

        if (textureUsageFlags & TextureUsage::TEXTURE_BINDING)
        {
            bindFlags |= D3D11_BIND_SHADER_RESOURCE;
        }
        if (textureUsageFlags & TextureUsage::RENDER_ATTACHMENT)
        {
            bindFlags |= D3D11_BIND_RENDER_TARGET;
        }

        if (bindFlags == 0)
        {
            throw new std::runtime_error("D3D11Texture2D::Convert: Unknown texture usage flags.");
        }

        return bindFlags;
    }

    D3D11_FILTER D3D11Texture2D::Convert(SamplerMinFilter minFilter, SamplerMagFilter magFilter)
    {
        if(minFilter == SamplerMinFilter::NEAREST && magFilter == SamplerMagFilter::NEAREST)
        {
            return D3D11_FILTER_MIN_MAG_MIP_POINT;
        }
        else if(minFilter == SamplerMinFilter::NEAREST && magFilter == SamplerMagFilter::LINEAR)
        {
            return D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR;
        }
        else if(minFilter == SamplerMinFilter::LINEAR && magFilter == SamplerMagFilter::NEAREST)
        {
            return D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT;
        }
        else if(minFilter == SamplerMinFilter::LINEAR && magFilter == SamplerMagFilter::LINEAR)
        {
            return D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        }
        else
        {
            std::string msg = "D3D11Texture2D::Convert: Unknown min filter or mag filter.";
            LOG(msg);
            BREAKPOINT();
            throw std::runtime_error(msg.c_str());
        }
    }

    void D3D11Texture2D::Initialize()
    {
        D3D11_TEXTURE2D_DESC textureDesc = {};
        ZeroMemory(&textureDesc, sizeof(textureDesc));
        textureDesc.Width = m_imageData->Width;
        textureDesc.Height = m_imageData->Height;
        textureDesc.MipLevels = 1;
        textureDesc.ArraySize = 1;
        textureDesc.Format = Convert(m_format);
        textureDesc.SampleDesc.Count = 1;
        textureDesc.SampleDesc.Quality = 0;
        textureDesc.Usage = D3D11_USAGE_DEFAULT;
        textureDesc.BindFlags = Convert(m_textureUsageFlags);
        textureDesc.CPUAccessFlags = 0;
        textureDesc.MiscFlags = 0;

        HRESULT hr;
        if (m_imageData->Data != nullptr)
        {
            D3D11_SUBRESOURCE_DATA initData = {};
            initData.pSysMem = m_imageData->Data;
            initData.SysMemPitch = m_imageData->Width * 4;
            initData.SysMemSlicePitch = 0;

            hr = m_device->CreateTexture2D(&textureDesc, &initData, &Texture.p);
        }
        else
        {
            hr = m_device->CreateTexture2D(&textureDesc, nullptr, &Texture.p);
        }
        if (FAILED(hr))
        {
            std::string msg = "D3D11Texture2D::Initialize: Failed to create texture. HRESULT: " + std::to_string(hr);
            LOG(msg);
            BREAKPOINT();
            throw new std::runtime_error(msg.c_str());
        }

        // Create the resource view
        D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
        srvDesc.Format = textureDesc.Format;
        srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        srvDesc.Texture2D.MipLevels = 1;
        srvDesc.Texture2D.MostDetailedMip = 0;

        hr = m_device->CreateShaderResourceView(Texture, &srvDesc, &TextureView.p);

        if (FAILED(hr))
        {
            std::string msg = "D3D11Texture2D::Initialize: Failed to create shader resource view. HRESULT: " + std::to_string(hr);
            LOG(msg);
            BREAKPOINT();
            throw new std::runtime_error(msg.c_str());
        }

        D3D11_FILTER filter = Convert(m_minFilter, m_magFilter);

        D3D11_SAMPLER_DESC samplerDesc = {};
        samplerDesc.Filter = filter;
        samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
        samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
        samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
        samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
        samplerDesc.MinLOD = 0;
        samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

        hr = m_device->CreateSamplerState(&samplerDesc, &Sampler.p);

        if (FAILED(hr))
        {
            std::string msg = "D3D11Texture2D::Initialize: Failed to create sampler state. HRESULT: " + std::to_string(hr);
            LOG(msg);
            BREAKPOINT();
            throw new std::runtime_error(msg.c_str());
        }
    }

    void D3D11Texture2D::Release()
    {
        TextureView.Release();
        Sampler.Release();
        Texture.Release();
    }
}

#endif