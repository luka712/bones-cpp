#if USE_METAL 

#include "effects/metal/MetalGrayscaleEffect.hpp"

namespace bns
{
#pragma region Implementation

    MetalGrayscaleEffectImpl::MetalGrayscaleEffectImpl(const Framework &framework)
        : MetalEffectImpl(framework)
    {
    }

#pragma endregion

} // namespace bns

#endif // __APPLE__