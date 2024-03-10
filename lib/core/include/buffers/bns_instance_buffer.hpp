#ifndef BNS_INSTANCE_BUFFER

#define BNS_INSTANCE_BUFFER

#include "bns_types.hpp"
#include <vector>

namespace bns
{

    template <typename T>
    class InstanceBuffer
    {
    protected:
        /// @brief The number of instances that buffer supoorts. 1 by default.
        u32 m_instanceCount;

        std::string m_label;

    public:
        /// @brief Constructor for the constant buffer
        /// @param label The label of the buffer.
        /// @param instanceCount The number of instances that buffer supoorts. 1 by default.
        InstanceBuffer(std::string label, u32 instanceCount = 1) 
        {
            m_label = label;
            m_instanceCount = instanceCount;
        }

        /// @brief The number of instances that buffer supoorts. 1 by default.
        /// @return The instace count.
        inline u32 GetInstanceCount() const { return m_instanceCount; }

        /// @brief The label of the buffer.
        /// @return The label.
        inline std::string GetLabel() const { return m_label; }

        /// @brief Initialize the constant buffer.
        /// @param data The data to be copied to the buffer.
        /// @param isWritable Whether the buffer is writable.
        /// @return The instance buffer.
        virtual void Initialize(std::vector<T> &data, bool isWritable = false) = 0;

        /// @brief Update the constant buffer.
        virtual void Update(std::vector<T> &data, i32 instance = 1) = 0;

        /// @brief Dispose the constant buffer.
        virtual void Dispose() = 0;
    };
}

#endif
