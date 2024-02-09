#if USE_D3D11

#ifndef BNS_D3D11_BUFFER_UTIL_HPP

#define BNS_D3D11_BUFFER_UTIL_HPP

#include "BnsDirectX11.hpp"
#include "bns_types.hpp"
#include <vector>
#include <exception>

namespace bns
{
    class D3D11BufferUtil
    {
    public:
        /// @brief Creates a vertex buffer
        /// @param device Creates a vertex buffer
        /// @param data The data to be copied to the buffer
        /// @return The vertex buffer
        static CComPtr<ID3D11Buffer> CreateVertexBuffer(CComPtr<ID3D11Device> device, std::vector<f32> data);

        /// @brief Creates a vertex buffer
        /// @param device Creates a vertex buffer
        /// @param byteSize The size of the buffer in bytes
        /// @return The vertex buffer
        static CComPtr<ID3D11Buffer> CreateVertexBuffer(CComPtr<ID3D11Device> device, size_t byteSize);

        /// @brief Create an D3D11 index buffer
        /// @tparam T - the type of data. Usually should be u16 or u32
        /// @param device The D3D11 device
        /// @param data The data to be copied to the buffer
        /// @return The index buffer
        template <typename T>
        static CComPtr<ID3D11Buffer> CreateIndexBuffer(CComPtr<ID3D11Device> device,
                                                       std::vector<T> data)
        {
            D3D11_BUFFER_DESC desc = {};
            desc.Usage = D3D11_USAGE_DEFAULT;
            desc.ByteWidth = data.size() * sizeof(T);
            desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
            desc.CPUAccessFlags = 0;
            desc.MiscFlags = 0;

            D3D11_SUBRESOURCE_DATA initData = {};
            initData.pSysMem = data.data();
            initData.SysMemPitch = 0;
            initData.SysMemSlicePitch = 0;

            CComPtr<ID3D11Buffer> buffer;
            HRESULT hr = device->CreateBuffer(&desc, &initData, &buffer);

            if (FAILED(hr))
            {
                throw std::exception("D3D11BufferUtil::CreateIndexBuffer: Failed to create index buffer");
            }

            return buffer;
        }

        /// @brief Creates a constant buffer
        /// @param device The D3D11 device
        /// @param byteSize The size of the buffer in bytes
        /// @return The constant buffer
        static CComPtr<ID3D11Buffer> CreateConstantBuffer(CComPtr<ID3D11Device> device, size_t byteSize);
    };
}

#endif

#endif // USE_D3D11