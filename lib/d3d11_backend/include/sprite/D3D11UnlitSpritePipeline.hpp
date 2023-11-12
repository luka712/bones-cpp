#if USE_D3D11

#ifndef BNS_UNLIT_SPRITE_PIPELINE_D3D11

#define BNS_UNLIT_SPRITE_PIPELINE_D3D11

#include "Constants.hpp"
#include <vector>
#include "Types.hpp"
#include "texture/D3D11Texture2D.hpp"

#define FLOATS_PER_VERTEX 9
#define FLOATS_PER_INSTANCE (4 * FLOATS_PER_VERTEX)

namespace bns
{
    class D3D11UnlitSpritePipeline final
    {
    private:
        CComPtr<ID3D11VertexShader> m_vertexShader;
        CComPtr<ID3D11PixelShader> m_pixelShader;
        CComPtr<ID3D11InputLayout> m_inputLayout;
        CComPtr<ID3D11BlendState> m_blendState;

        D3D11Texture2D *m_texture;

    public:
        D3D11UnlitSpritePipeline(CComPtr<ID3D11VertexShader> vertexShader,
                                 CComPtr<ID3D11PixelShader> pixelShader,
                                 CComPtr<ID3D11InputLayout> inputLayout,
                                 CComPtr<ID3D11BlendState> blendState,
                                 D3D11Texture2D *texture);

        ~D3D11UnlitSpritePipeline();

        /// @brief The instance index which is used to tell how many instances are in buffer and to be drawn.
        u32 InstanceIndex;

        /// @brief The vertex buffer data.
        f32 DataArray[SPRITE_RENDERER_MAX_SPRITES_PER_DRAW * FLOATS_PER_INSTANCE];

        /// @brief Create a sprite pipeline
        /// @param device The D3D11 device
        /// @param texture The texture
        /// @return The sprite pipeline
        static D3D11UnlitSpritePipeline *Create(CComPtr<ID3D11Device> device, D3D11Texture2D *texture);

        /// @brief Gets the vertex shader
        /// @return The vertex shader
        inline const CComPtr<ID3D11VertexShader> &GetVertexShader() const { return m_vertexShader; }

        /// @brief Gets the pixel shader
        /// @return The pixel shader
        inline const CComPtr<ID3D11PixelShader> &GetPixelShader() const { return m_pixelShader; }

        /// @brief Gets the input layout
        /// @return The input layout
        inline const CComPtr<ID3D11InputLayout> &GetInputLayout() const { return m_inputLayout; }

        /// @brief Gets the blend state
        /// @return The blend state
        inline const CComPtr<ID3D11BlendState> &GetBlendState() const { return m_blendState; }

        /// @brief Gets the texture
        /// @return The texture
        inline const D3D11Texture2D *GetTexture() const { return m_texture; }

        /// @brief Release the pipeline
        void Release();
    };
}

#endif // BNS_UNLIT_SPRITE_PIPELINE_D3D11

#endif // USE_D3D11