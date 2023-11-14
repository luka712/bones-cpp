#ifndef BNS_TYPE_H

#define BNS_TYPE_H

#include <stdint.h>

#if LOGGING_ENABLED
#include <stdio.h>
/// @brief Log if LOGGING_ENABLED is true
#define LOG(...) printf(__VA_ARGS__)
#else 
/// @brief Log if LOGGING_ENABLED is true
#define LOG(...)
#endif 

#if DEBUG_BREAKPOINT_ENABLED
/// @brief Breakpoint if DEBUG_BREAKPOINT_ENABLED is true
#define BREAKPOINT() __debugbreak()
#else
/// @brief Breakpoint if DEBUG_BREAKPOINT_ENABLED is true
#define BREAKPOINT()
#endif

#define PI 3.14159265358979323846f

enum class LifecycleState
{
   Created,
   Initialized,
   Released,
};

namespace bns
{
    typedef uint8_t u8;

    typedef int16_t i16;
    typedef uint16_t u16;

    typedef int32_t i32;
    typedef uint32_t u32;

    typedef int64_t i64;
    typedef uint64_t u64;

    typedef float f32;
} // namespace BNS
#endif