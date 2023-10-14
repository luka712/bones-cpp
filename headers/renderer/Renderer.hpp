#ifndef BNS_RENDERER_HPP

#define BNS_RENDERER_HPP

#include "data/Types.hpp"
#include "data/bns_math.hpp"
#include "textures/Texture2D.hpp"
#include "data/Vec2.hpp"

namespace bns
{
    class Framework;

    class Renderer
    {
    protected:
        Framework &m_framework;

        /**
         * @brief The texture to render to, if set, instead of rendering to screen, it will render to this texture.
         * Used for post processing.
         */
        Texture2D *m_renderTexture = nullptr;

        /// @brief The brightness texture. Every material should output 2nd color as brightness.
        /// @note This texture is used for bloom effect.
        Texture2D *m_brightnessTexture = nullptr;

        /**
         * @brief The size of the render buffer.
         */
        Vec2u m_bufferSize;

    public:
        Color ClearColor;

        Renderer(Framework &framework);

        /**
         * @brief Get the buffer size.
         */
        const Vec2u &GetBufferSize() const
        {
            return m_bufferSize;
        }

        /**
         * @brief Gets the view into swap chain texture.
         */
        virtual void *GetSwapChainTexture() = 0;

        /**
         * @brief Set the render texture.
         * @param texture - the texture to render to.
         *
         * Used when scene needs to be rendered to a texture.
         * Passing nullptr will render to the screen texture.
         */
        virtual void SetRenderTexture(Texture2D *texture);

        /**
         * @brief Unset the render texture.
         * Same as SetRenderTexture(nullptr).
         */
        virtual void UnsetRenderTexture();

        /// @brief Gets the brightness texture or nullptr if not set.
        /// @return The brightness texture or nullptr if not set.
        inline Texture2D* GetBrightnessTexture() const
        {
            return m_brightnessTexture;
        }

        /// @brief The brightness texture. Every material should output 2nd color as brightness.
        /// @note This texture is used for bloom effect.
        /// @param texture The brightness texture.
        virtual void SetBrightnessTexture(Texture2D *texture);

        /// @brief Unsets the brightness texture.
        /// Same as SetBrightnessTexture(nullptr).
        virtual void UnsetBrightnessTexture();

        /**
         * @brief Prepares the renderer.
         */
        virtual void BeginDraw() = 0;

        /**
         * @brief Ends the renderer.
         */
        virtual void EndDraw() = 0;

        /**
         * @brief Destroy the renderer.
         */
        virtual void Destroy() = 0;
    };
}

#endif // !BNS_RENDERER_HPP