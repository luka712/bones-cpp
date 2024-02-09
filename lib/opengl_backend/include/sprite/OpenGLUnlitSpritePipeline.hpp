#if USE_OPENGL

#ifndef BNS_UNLIT_SPRITE_PIPELINE_OPENGL

#define BNS_UNLIT_SPRITE_PIPELINE_OPENGL

#include "Constants.hpp"
#include <vector>
#include "bns_types.hpp"
#include "renderer/OpenGLRenderer.hpp"
#include "texture/OpenGLTexture2D.hpp"

#define FLOATS_PER_VERTEX 9
#define FLOATS_PER_INSTANCE (4 * FLOATS_PER_VERTEX)

namespace bns
{
    class OpenGLUnlitSpritePipeline final
    {
    private:
        GLuint m_program;
        GLint m_textureLocation;
        OpenGLTexture2D *m_texture;

    public:
        /// @brief The constructor.
        OpenGLUnlitSpritePipeline(GLuint program,
                                  GLint textureLocation,
                                  OpenGLTexture2D *texture);

        ~OpenGLUnlitSpritePipeline();

        /// @brief The instance index which is used to tell how many instances are in buffer and to be drawn.
        u32 InstanceIndex;

        /// @brief The vertex buffer data.
        f32 DataArray[SPRITE_RENDERER_MAX_SPRITES_PER_DRAW * FLOATS_PER_INSTANCE];

        /// @brief Create a sprite pipeline
        /// @param texture The texture
        /// @return The sprite pipeline
        static OpenGLUnlitSpritePipeline *Create(OpenGLTexture2D *texture);

        /// @brief Gets the program
        /// @return The program
        inline GLuint GetProgram() const { return m_program; }

        /// @brief Gets the texture
        /// @return The texture
        inline const OpenGLTexture2D *GetTexture() const { return m_texture; }

        /// @brief Gets the texture location
        /// @return The texture location
        inline GLint GetTextureLocation() const { return m_textureLocation; }

        /// @brief Release the pipeline
        void Release();
    };
}

#endif // BNS_UNLIT_SPRITE_PIPELINE_OPENGL

#endif // USE_OPENGL
