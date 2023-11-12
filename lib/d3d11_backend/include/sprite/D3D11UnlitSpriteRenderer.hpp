#pragma once

#if USE_D3D11

#ifndef BNS_UNLIT_SPRITE_RENDERER_D3D11_HPP

#define BNS_UNLIT_SPRITE_RENDERER_D3D11_HPP

#include "sprite/SpriteRenderer.hpp"
#include "renderer/D3D11Renderer.hpp"
#include "sprite/D3D11UnlitSpritePipeline.hpp"
#include "texture/D3D11Texture2D.hpp"
#include <map>
#include <stack>

namespace bns
{
    class D3D11UnlitSpriteRenderer final : public SpriteRenderer
    {
    private:
        /// @brief The renderer.
        D3D11Renderer *m_renderer;

        /// @brief The device.
        CComPtr<ID3D11Device> m_device;

        /// @brief The device context.
        CComPtr<ID3D11DeviceContext> m_deviceContext;

        /// @brief The index buffer.
        CComPtr<ID3D11Buffer> m_indexBuffer;

        /// @brief The projection view matrix buffer.
        CComPtr<ID3D11Buffer> m_projectionViewMatrixBuffer;

        /// @brief The brightness threshold buffer.
        CComPtr<ID3D11Buffer> m_brightnessThresholdBuffer;

        /// @brief All the allocated pipelines per texture. Pop from this pipeline to current draw pipelines.
        /// At the end of frame, push back to this pipeline from current draw pipelines.
        std::map<u32, std::stack<D3D11UnlitSpritePipeline *>> m_allocatedPipelines;

        /// @brief The current draw pipelines per texture. At the end of frame pop from this pipeline to allocated pipelines.
        /// If there is no allocated pipeline, create a new one and push it here.
        std::map<u32, std::stack<D3D11UnlitSpritePipeline *>> m_currentDrawPipelines;

        /// @brief The stack of vertex buffers.
        std::stack<CComPtr<ID3D11Buffer>> m_vertexBufferStack;

        /// @brief Setup the index buffer.
        void SetupIndexBuffer();

                /// @brief Gets or creates a pipeline for the texture.
        /// Creation is handled internally, so just get reference.
        D3D11UnlitSpritePipeline &GetPipeline(D3D11Texture2D *texture);

    public:
        D3D11UnlitSpriteRenderer(Renderer *renderer);

        void Initialize() override;

        void BeginFrame() override;

        void Draw(Texture2D *texture,
                  const Rect &drawRect,
                  const Rect &sourceRect,
                  const Color &color,
                  f32 rotationInRadians, const Vec2f &rotationOrigin) override;

        void DrawString(SpriteFont *font,
                        const std::string &text,
                        const Vec2f &position,
                        const Color &color,
                        const f32 scale) override;

        void EndFrame() override;
    };
}

#endif // !BNS_UNLIT_SPRITE_RENDERER_D3D11_HPP

#endif // USE_D3D11