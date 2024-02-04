#include "time/TimeManager.hpp"

namespace bns
{
    TimeManager::TimeManager(f32 desiredFPS)
        : m_desiredMSPerFrame(1000.0f / desiredFPS), m_elapsedTime(0)
    {
        m_time.DeltaTimeMS = 0.0f;
        m_time.DeltaTimeSec = 0.0f;
    }

    f32 TimeManager::GetFPS()
    {
        return  m_time.DeltaTimeMS != 0.0f ? 1000.0f / m_time.DeltaTimeMS : 0.0f;
    }
} // namespace bns