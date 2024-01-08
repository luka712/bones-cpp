#ifndef BNS_RENDERER_HPP

#define BNS_RENDERER_HPP

#include "Types.hpp"
#include "Math.hpp"
#include "texture/Texture2D.hpp"
#include "Vec2.hpp"
#include "RenderingBackendTypes.hpp"

namespace bns
{
    /// @brief The renderer type.
    enum class RendererType
    {
        /// @brief Default option. If none is set the framework will try to use the best available renderer.
        None,
        Metal,
        D3D11,
        D3D12,
        OpenGL,
        OpenGLES,
        WebGPU,
        Vulkan
    };

    class Renderer
    {
    protected:
        /// @brief The texture to render to, if set, instead of rendering to screen, it will render to this texture.
        /// Used for post processing.
        Texture2D *m_renderTexture = nullptr;

        /// @brief The brightness texture. Every material should output 2nd color as brightness.
        /// @note This texture is used for bloom effect.
        Texture2D *m_brightnessTexture = nullptr;

        /// @brief The size of the render buffer.
        Vec2i m_bufferSize;

    public:
        /// @brief The clear color.
        /// The color to which renderer will be cleared at the beginning of each frame.
        Color ClearColor;

        /// @brief The front face.
        /// The front face of the vertices in the scene. By default it is counter clockwise.
        FrontFace FrontFace;

        Renderer();

        /// @brief Get the buffer size.
        const Vec2i &GetBufferSize() const { return m_bufferSize; }

        /// @brief Gets the renderer type.
        /// @return The renderer type.
        virtual RendererType GetRendererType() const = 0;

        /// @brief Gets the view into swap chain texture.
        virtual void *GetSwapChainTexture() = 0;

        /// @brief Set the render texture.
        /// @param texture - the texture to render to.
        /// Used when scene needs to be rendered to a texture.
        /// Passing nullptr will render to the screen texture.
        virtual void SetRenderTexture(Texture2D *texture);

        /// @brief Unset the render texture.
        /// Same as SetRenderTexture(nullptr).
        virtual void UnsetRenderTexture();

        /// @brief Gets the brightness texture or nullptr if not set.
        /// @return The brightness texture or nullptr if not set.
        inline Texture2D *GetBrightnessTexture() const
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

        /// @brief Prepares the renderer.
        virtual void BeginDraw() = 0;

        /// @brief Ends the renderer.
        virtual void EndDraw() = 0;

        /// @brief Destroy the renderer.
        virtual void Destroy() = 0;
    };
}

#endif // !BNS_RENDERER_HPP
