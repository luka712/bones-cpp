#ifndef BNS_RENDERER_HPP

#define BNS_RENDERER_HPP

#include "bns_types.hpp"
#include "bns_math.hpp"
#include "texture/bns_texture2d.hpp"
#include "math/bns_vec2.hpp"
#include "bns_rendering_backend_types.hpp"

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

    /// @brief The presentation mode.
    enum class SurfacePresentationMode
    {
        /// @brief The immediate presentation mode. The frame will be presented immediately.
        SingleBuffer,

        /// @brief The vsync presentation mode. One back buffer and one front buffer. We will wait for the next vsync to present the frame. 
        DoubleBuffering,
 
        /// @brief The triple buffering presentation mode. Two back buffers and one front buffer. Instead of back buffer having to wait for vsync, we can write to another back buffer.
        TripleBuffering
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

        /// @brief The number of frames in flight.
        u32 m_framesInFlight;

        /// @brief The size of the render buffer.
        Vec2i m_bufferSize;

        /// @brief The presentation mode.
        SurfacePresentationMode m_presentationMode;

    public:
        /// @brief The clear color.
        /// The color to which renderer will be cleared at the beginning of each frame.
        Color ClearColor;

        /// @brief The front face.
        /// The front face of the vertices in the scene. By default it is counter clockwise.
        FrontFace FrontFace;

        /// @brief The constructor.
        /// @param presentationMode The presentation mode. By default it is double buffering. 
        Renderer(SurfacePresentationMode presentationMode = SurfacePresentationMode::DoubleBuffering);

        /// @brief Get the buffer size.
        const Vec2i &GetBufferSize() const { return m_bufferSize; }

        /// @brief The number of frames in flight.
        u32 GetFramesInFlight() const { return m_framesInFlight; }

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
