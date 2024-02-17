#if USE_OPENGL

#ifndef BNS_UNLIT_SPRITE_PIPELINE_OPENGL400

#define BNS_UNLIT_SPRITE_PIPELINE_OPENGL400

#include "Constants.hpp"
#include <vector>
#include "bns_types.hpp"
#include "renderer/OpenGLbns_renderer.hpp"
#include "texture/OpenGLTexture2D.hpp"

#define FLOATS_PER_VERTEX 9
#define FLOATS_PER_INSTANCE (4 * FLOATS_PER_VERTEX)

namespace bns
{
    /// @brief The OpenGL 4.0 unlit sprite pipeline. To not be used with regular OpenGL 450 renderer.
    /// @note This is fallback for OpenGL 4.0 in case if 4.5 is not available on the system (e.g. macOS)
    class OpenGL400UnlitSpritePipeline final
    {
    private:
        GLuint m_program;
        GLint m_textureLocation;
        GLint m_projectionViewLocation;
        OpenGLTexture2D *m_texture;

    public:
        /// @brief The constructor.
        OpenGL400UnlitSpritePipeline(GLuint program,
                                  GLint textureLocation,
                                  GLint projectionViewLocation,
                                  OpenGLTexture2D *texture);

        ~OpenGL400UnlitSpritePipeline();

        /// @brief The instance index which is used to tell how many instances are in buffer and to be drawn.
        u32 InstanceIndex;

        /// @brief The vertex buffer data.
        f32 DataArray[SPRITE_RENDERER_MAX_SPRITES_PER_DRAW * FLOATS_PER_INSTANCE];

        /// @brief Create a sprite pipeline
        /// @param texture The texture
        /// @return The sprite pipeline
        static OpenGL400UnlitSpritePipeline *Create( OpenGLTexture2D *texture);

        /// @brief Gets the program
        /// @return The program
        inline GLuint GetProgram() const { return m_program; }

        /// @brief Gets the texture
        /// @return The texture
        inline const OpenGLTexture2D *GetTexture() const { return m_texture; }

        /// @brief Gets the texture location
        /// @return The texture location
        inline GLint GetTextureLocation() const { return m_textureLocation; }

        /// @brief Gets the projection view location
        /// @return The projection view location
        inline GLint GetProjectionViewLocation() const { return m_projectionViewLocation; }

        /// @brief Release the pipeline
        void Release();
    };
}

#endif // BNS_UNLIT_SPRITE_PIPELINE_OPENGL

#endif // USE_OPENGL
