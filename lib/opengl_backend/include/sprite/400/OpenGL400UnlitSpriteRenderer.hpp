#pragma once

#if USE_OPENGL

#ifndef BNS_UNLIT_SPRITE_RENDERER_OPENGL_HPP_400

#define BNS_UNLIT_SPRITE_RENDERER_OPENGL_HPP_400

#include "sprite/bns_sprite_renderer.hpp"
#include "renderer/OpenGLbns_renderer.hpp"
#include "sprite/400/OpenGL400UnlitSpritePipeline.hpp"
#include "texture/OpenGLTexture2D.hpp"
#include <unordered_map>
#include <stack>

namespace bns
{
    /// @brief Placeholder class that holds vao and vbo.
    struct VAOBuffer 
    {
        /// @brief The vertex array object id.
        GLuint VAO;
        /// @brief The vertex buffer object id.
        GLuint VBO;
    };

    class OpenGL400UnlitSpriteRenderer final : public SpriteRenderer
    {
    private:
        /// @brief The renderer.
        OpenGLRenderer *m_renderer;

        /// @brief The index buffer.
        GLuint m_indexBuffer;

        /// @brief The brightness threshold buffer.
        GLuint m_brightnessThresholdBuffer;

        /// @brief All the allocated pipelines per texture. Pop from this pipeline to current draw pipelines.
        /// At the end of frame, push back to this pipeline from current draw pipelines.
        std::unordered_map<GLuint, std::stack<OpenGL400UnlitSpritePipeline *>> m_allocatedPipelines;

        /// @brief The current draw pipelines per texture. At the end of frame pop from this pipeline to allocated pipelines.
        /// If there is no allocated pipeline, create a new one and push it here.
        std::unordered_map<GLuint, std::stack<OpenGL400UnlitSpritePipeline *>> m_currentDrawPipelines;

        /// @brief The stack of vertex buffers.
        std::stack<VAOBuffer*> m_vertexBufferStack;

        /// @brief Setup the index buffer.
        void SetupIndexBuffer();

        /// @brief Creates the vertex buffer.
        /// @return The vertex buffer id.
        VAOBuffer* CreateVertexBuffer();

        /// @brief Gets or creates a pipeline for the texture.
        /// Creation is handled internally, so just get reference.
        OpenGL400UnlitSpritePipeline &GetPipeline(OpenGLTexture2D *texture);

    public:
        OpenGL400UnlitSpriteRenderer(Renderer *renderer);

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

#endif // !BNS_UNLIT_SPRITE_RENDERER_OpenGL_HPP

#endif // BNS_UNLIT_SPRITE_RENDERER_OPENGL_HPP