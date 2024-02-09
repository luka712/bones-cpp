#ifndef BNS_TIME_HPP

#define BNS_TIME_HPP

#include "bns_types.hpp"

namespace bns 
{
     /// @brief The time information.
    struct Time 
    {
        /// @brief The delta time in milliseconds.
        f32 DeltaTimeMS;

        /// @brief The delta time in seconds.
        f32 DeltaTimeSec;

        /// @brief Total elapsed time since start of game in milliseconds.
        f32 ElapsedTimeMS;

        /// @brief Total elapsed time since start of game in seconds.
        f32 ElapsedTimeSec;

        /// @brief The constructor.
        Time();
    };

}

#endif 