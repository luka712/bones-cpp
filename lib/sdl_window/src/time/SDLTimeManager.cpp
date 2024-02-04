#include "time/SDLTimeManager.hpp"
#include <SDL2/SDL.h>

namespace bns
{
    SDLTimeManager::SDLTimeManager(f32 desiredFPS)
        : TimeManager(desiredFPS)
    {
    }

    void SDLTimeManager::PrepareStart()
    {
        m_time.ElapsedTimeMS = SDL_GetTicks64();
    }

    void SDLTimeManager::Start()
    {
        m_elapsedTime = SDL_GetTicks64();
    }

    void SDLTimeManager::End()
    {
        // make sure delta time is in ms.
        f32 delta_time = (SDL_GetTicks64() - m_elapsedTime);

        if (m_desiredMSPerFrame > delta_time)
        {
            f32 delay = m_desiredMSPerFrame - delta_time;
            delta_time += delay;

            SDL_Delay(static_cast<u32>(delay));
        }
        m_time.DeltaTimeMS = delta_time;
        m_time.DeltaTimeSec = m_time.DeltaTimeMS / 1000.0f;
        m_time.ElapsedTimeMS += m_time.DeltaTimeMS;
        m_time.ElapsedTimeSec = m_time.ElapsedTimeMS / 1000.0f;
    }
} // namespace bns