#ifndef BNS_UNLIT_RENDER_PIPELINE_HPP

#define BNS_UNLIT_RENDER_PIPELINE_HPP

#include "renderer/bns_renderer.hpp"
#include "texture/bns_texture2d.hpp"
#include "math/bns_vec2.hpp"
#include "bns_color.hpp"

namespace bns
{
    /// @brief The unlit render pipeline.
    class UnlitRenderPipeline
    {
    protected:
        Texture2D *m_diffuseTexture;
        Color m_diffuseColor;
        Vec2f m_textureTilling;

    public:
        /// @brief Initialize the pipeline.
        virtual void Initialize() = 0;

          /// @brief Set the diffuse texture.
        inline Color GetDiffuseColor() const { return m_diffuseColor; }

        /// @brief Set the diffuse texture.
        virtual void SetDiffuseColor(Color color) = 0;

        /// @brief Get the texture tilling.
        inline Vec2f GetTextureTilling() const { return m_textureTilling; }

        /// @brief Set the texture tilling.
        virtual void SetTextureTilling(Vec2f tilling) = 0;

        /// @brief Get the diffuse texture.
        inline Texture2D *GetDiffuseTexture() const { return m_diffuseTexture; }

        /// @brief Set the diffuse texture.
        virtual void SetDiffuseTexture(Texture2D *texture) = 0;
    };
} // namespace bns

#endif