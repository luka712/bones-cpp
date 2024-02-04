#ifndef BNS_SDL_TIME_MANAGER_HPP

#define BNS_SDL_TIME_MANAGER_HPP

#include "time/TimeManager.hpp"

namespace bns
{
    /// @brief The SDL implementation of the time manager.
    class SDLTimeManager : public TimeManager
    {
    public:
        SDLTimeManager(f32 desiredFPS);

        void PrepareStart() override;
        void Start() override;
        void End() override;
    };
} // namespace bns

#endif