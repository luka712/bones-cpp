#ifndef BNS_INSTANCE_BUFFER

#define BNS_INSTANCE_BUFFER

#include "bns_types.hpp"

namespace bns
{

    template <typename T>
    class InstanceBuffer
    {
    protected:
        /// @brief The number of instances that buffer supoorts. 1 by default.
        u32 m_instanceCount;

    public:
        /// @brief Constructor for the constant buffer
        /// @param instanceCount The number of instances that buffer supoorts. 1 by default.
        InstanceBuffer(u32 instanceCount = 1) : m_instanceCount(instanceCount) {}

        /// @brief The number of instances that buffer supoorts. 1 by default.
        /// @return The instace count.
        inline u32 GetInstanceCount() const
        {
            return m_instanceCount;
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
