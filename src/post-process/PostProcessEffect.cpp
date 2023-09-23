#include "post-process/PostProcessEffect.hpp"
#include "Framework.hpp"

namespace bns
{
    PostProcessEffect::PostProcessEffect(const Framework &framework)
        : m_framework(framework), m_texture(nullptr)
    {
    }
} // namespace bns