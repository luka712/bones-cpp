#if USE_D3D11

#include "util/D3D11BufferUtil.hpp"
#include <exception>

namespace bns
{
    CComPtr<ID3D11Buffer> D3D11BufferUtil::CreateConstantBuffer(CComPtr<ID3D11Device> device, size_t byteSize)
    {
        // align to 16 bytes
        if (byteSize % 16 != 0)
        {
            byteSize += 16 - (byteSize % 16);
        }

        CComPtr<ID3D11Buffer> buffer;

        CD3D11_BUFFER_DESC desc;
        desc.ByteWidth = byteSize;
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        desc.CPUAccessFlags = 0;
        desc.MiscFlags = 0;
        desc.StructureByteStride = 0;

        HRESULT hr = device->CreateBuffer(&desc, nullptr, &buffer.p);

        if (FAILED(hr))
        {
            throw std::exception("D3D11BufferUtil::CreateConstantBuffer: Failed to create constant buffer");
        }

        return buffer;
    }

    CComPtr<ID3D11Buffer> D3D11BufferUtil::CreateVertexBuffer(CComPtr<ID3D11Device> device, std::vector<f32> data)
    {
        CComPtr<ID3D11Buffer> buffer;

        CD3D11_BUFFER_DESC desc;
        desc.ByteWidth = data.size() * sizeof(f32);
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        desc.CPUAccessFlags = 0;
        desc.MiscFlags = 0;
        desc.StructureByteStride = 0;

        D3D11_SUBRESOURCE_DATA initData = {};
        initData.pSysMem = data.data();
        initData.SysMemPitch = 0;
        initData.SysMemSlicePitch = 0;

        HRESULT hr = device->CreateBuffer(&desc, &initData, &buffer.p);

        if (FAILED(hr))
        {
            throw std::exception("D3D11BufferUtil::CreateVertexBuffer: Failed to create vertex buffer");
        }

        return buffer;
    }

    CComPtr<ID3D11Buffer> D3D11BufferUtil::CreateVertexBuffer(CComPtr<ID3D11Device> device, size_t byteSize)
    {
        CComPtr<ID3D11Buffer> buffer;

        CD3D11_BUFFER_DESC desc;
        desc.ByteWidth = byteSize;
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        desc.CPUAccessFlags = 0;
        desc.MiscFlags = 0;
        desc.StructureByteStride = 0;

        HRESULT hr = device->CreateBuffer(&desc, nullptr, &buffer.p);

        if (FAILED(hr))
        {
            throw std::exception("D3D11BufferUtil::CreateVertexBuffer: Failed to create vertex buffer");
        }

        return buffer;
    }

}

#endif