#ifndef BNS_POST_PROCESS_EFFECT_HPP

#define BNS_POST_PROCESS_EFFECT_HPP

#include "textures/Texture2D.hpp"

namespace bns
{
    class Framework;

    class PostProcessEffect
    {
    protected:
        const Framework &m_framework;

        /**
         * @brief The source texture.
         * This is the texture that we want to apply the effect to.
         */
        Texture2D *m_sourceTexture = nullptr;

    public:
        PostProcessEffect(const Framework &framework);

        /**
         * @brief Get the source texture.
         * @return The source texture.
         * This is the texture that we want to apply the effect to.
         */
        inline Texture2D *GetSourceTexture() const
        {
            return m_sourceTexture;
        }

        /**
         * @brief Initialize the effect.
        */
        virtual void Initialize() = 0;

        /**
         * @brief Draw the effect to the destination texture.
         * @param destinationTexture The destination texture.
         * This is a texture to which we want to render, usually the screen texture.
         * But can be any other texture if there are multiple post process effects.
         */
        virtual void Draw(void *destinationTexture) = 0;
    };
} // namespace bns

#endif // BNS_POST_PROCESS_EFFECT_HPP