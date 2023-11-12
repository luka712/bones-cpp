#ifndef BNS_POST_PROCESS_EFFECT_HPP

#define BNS_POST_PROCESS_EFFECT_HPP

#include "texture/Texture2D.hpp"

namespace bns
{
    class Framework;

    class Effect
    {
    protected:
        const Framework &m_framework;

    public:
        Effect(const Framework &framework);

        /// @brief Get the source texture.
        /// @return The source texture.
        /// This is the texture that we want to apply the effect to.
        /// Usually this is the texture that scene should be drawn to.
        virtual Texture2D *GetSourceTexture() = 0;

        /// @brief Set the source texture.
        /// @param sourceTexture The source texture.
        /// This is the texture that we want to apply the effect to.
        virtual void SetSourceTexture(Texture2D *sourceTexture) = 0;
        
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

        // TODO: destroy
    };
} // namespace bns

#endif // BNS_POST_PROCESS_EFFECT_HPP