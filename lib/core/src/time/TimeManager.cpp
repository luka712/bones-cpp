#include "time/TimeManager.hpp"

namespace bns
{
    TimeManager::TimeManager(f32 desiredFPS)
        : m_desiredMSPerFrame(1000.0f / desiredFPS), m_elapsedTime(0), m_framesCount(0)
    {
    }

    f32 TimeManager::GetFPS()
    {
        return m_framesCount / (m_elapsedTime / 1000.0f);
    }
} // namespace bns