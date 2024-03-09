#ifndef BNS_INDEX_BUFFER_HPP

#define BNS_INDEX_BUFFER_HPP

#include "bns_types.hpp"
#include <vector>
#include <string>

namespace bns
{
    /// @brief The index buffer.
    class IndexBuffer
    {
    protected:
        u32 m_indicesCount;
        size_t m_byteSize;
        std::string m_label;

    public:
        /// @brief Constructor for the index buffer.
        IndexBuffer(std::string label = "");

        /// @brief Get the number of indices in the buffer.
        /// @return The number of indices.
        inline u32 GetIndicesCount() const
        {
            return m_indicesCount;
        }

        /// @brief Get the byte size of the buffer.
        /// @return The byte size.
        inline size_t GetByteSize() const
        {
            return m_byteSize;
        }

        /// @brief Get the label of the buffer.
        /// @return The label.
        inline const std::string& GetLabel() const
        {
            return m_label;
        }

        /// @brief Initialize the index buffer.
        /// @param data The data to be copied to the buffer.
        virtual void Initialize(std::vector<u16> &data) = 0;

        /// @brief Dispose the index buffer.
        virtual void Dispose() = 0;
    };
}

#endif
