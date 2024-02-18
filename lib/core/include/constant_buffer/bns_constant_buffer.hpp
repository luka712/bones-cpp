#ifndef BNS_CONSTANT_BUFFER

#define BNS_CONSTANT_BUFFER

#include "bns_types.hpp"

namespace bns
{

    template <typename T>
    class ConstantBuffer
    {
    private:
        u32 m_instanceCount;

    public:
        /// @brief Constructor for the constant buffer
        /// @param instanceCount The number of instances that buffer supoorts. 1 by default.
        ConstantBuffer(u32 instanceCount = 1) : m_instanceCount(instanceCount) {}

        /// @brief The number of instances that buffer supoorts. 1 by default.
        /// @return
        inline const u32 GetInstanceCount() const
        {
            return m_instnaceCount;
        }

        /// @brief Initialize the constant buffer.
        virtual void Initialize() = 0;

        /// @brief Update the constant buffer.
        virtual void Update(T &data) = 0;

        /// @brief Dispose the constant buffer.
        virtual void Dispose() = 0;
    };
}

#endif