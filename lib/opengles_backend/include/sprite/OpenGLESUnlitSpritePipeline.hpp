#if USE_OPENGLES

#ifndef BNS_UNLIT_SPRITE_PIPELINE_OpenGLES

#define BNS_UNLIT_SPRITE_PIPELINE_OpenGLES

#include "Constants.hpp"
#include <vector>
#include "Types.hpp"
#include "texture/OpenGLESTexture2D.hpp"

#define FLOATS_PER_VERTEX 9
#define FLOATS_PER_INSTANCE (4 * FLOATS_PER_VERTEX)

namespace bns
{
    class OpenGLESUnlitSpritePipeline final
    {
    private:
        GLuint m_program;
        GLint m_textureLocation;
        OpenGLESTexture2D *m_texture;

    public:
        /// @brief The constructor.
        OpenGLESUnlitSpritePipeline(GLuint program,
                                  GLint textureLocation,
                                  OpenGLESTexture2D *texture);

        ~OpenGLESUnlitSpritePipeline();

        /// @brief The instance index which is used to tell how many instances are in buffer and to be drawn.
        u32 InstanceIndex;

        /// @brief The vertex buffer data.
        f32 DataArray[SPRITE_RENDERER_MAX_SPRITES_PER_DRAW * FLOATS_PER_INSTANCE];

        /// @brief Create a sprite pipeline
        /// @param device The OpenGLES device
        /// @param texture The texture
        /// @return The sprite pipeline
        static OpenGLESUnlitSpritePipeline *Create(OpenGLESTexture2D *texture);

        /// @brief Gets the program
        /// @return The program
        inline const GLuint GetProgram() const { return m_program; }

        /// @brief Gets the texture
        /// @return The texture
        inline const OpenGLESTexture2D *GetTexture() const { return m_texture; }

        /// @brief Gets the texture location
        /// @return The texture location
        inline const GLint GetTextureLocation() const { return m_textureLocation; }

        /// @brief Release the pipeline
        void Release();
    };
}

#endif // BNS_UNLIT_SPRITE_PIPELINE_OpenGLES

#endif // USE_OpenGLES