#ifndef BNS_UNIFORM_BUFFER

#define BNS_UNIFORM_BUFFER

#include "bns_types.hpp"

namespace bns
{

    template <typename T>
    class UniformBuffer
    {
    public:
        /// @brief Initialize the constant buffer.
        virtual void Initialize() = 0;

        /// @brief Update the constant buffer.
        virtual void Update(T &data) = 0;

        /// @brief Dispose the constant buffer.
        virtual void Dispose() = 0;
    };
}

#endif
