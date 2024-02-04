#ifndef BNS_TIME_MANAGER_HPP

#define BNS_TIME_MANAGER_HPP

#include "Types.hpp"

namespace bns
{
    /// @brief The time information.
    struct Time 
    {
        /// @brief The delta time in milliseconds.
        f32 DeltaTimeMS;

        /// @brief Total elapsed time since start of game in milliseconds.
        f32 ElapsedTimeMS;

        /// @brief Total elapsed time since start of game in seconds.
        f32 ElapsedTimeSec;
    };

    /// @brief The time manager which is used to manage time.
    class TimeManager
    {
    protected:

        /// @brief The time information.
        Time m_time;

        /// @brief How many milliseconds per frame the game should run at.
        /// For example, 60 FPS would be 16.6666667f.
        f32 m_desiredMSPerFrame;

        /// @brief Amount of elapsed time since the game started.
        u64 m_elapsedTime;

        /// @brief Number of frames that have been rendered.
        u64 m_framesCount;

    public:
        /// @brief The constructor.
        /// @param desiredFPS The desired frames per second.
        TimeManager(f32 desiredFPS);

        /// @brief Gets the time information.
        /// @return The time information.
        inline Time GetTime() const { return m_time; }

        /// @brief Gets the average frames per second.
        f32 GetFPS();

        /// @brief Prepare the time manager for a start. Ideally this should be called before the game loop starts.
        virtual void PrepareStart() = 0;

        /// @brief Start the time manager. This should be called at the start of the game loop.
        virtual void Start() = 0;

        /// @brief End the time manager. This should be called at the end of the game loop.
        virtual void End() = 0;
    };
}

#endif