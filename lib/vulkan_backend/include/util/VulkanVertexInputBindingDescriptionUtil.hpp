#ifndef BNS_VULKAN_VERTEX_INPUT_BINDING_DESCRIPTION_UTIL_HPP

#define BNS_VULKAN_VERTEX_INPUT_BINDING_DESCRIPTION_UTIL_HPP

#include "BnsVulkan.hpp"
#include <vector>
#include <map>
#include "buffer_layout/BufferLayoutData.hpp"

namespace bns
{
    
    /// @brief Utility class for creating @ref VkVertexInputBindingDescription structs
    class VulkanVertexInputBindingDescriptionUtil final
    {
    private:
        inline static std::map<VertexFormat, VkFormat> m_vertexFormatMap = {
            {VertexFormat::Float32x1, VK_FORMAT_R32_SFLOAT},
            {VertexFormat::Float32x2, VK_FORMAT_R32G32_SFLOAT},
            {VertexFormat::Float32x3, VK_FORMAT_R32G32B32_SFLOAT},
            {VertexFormat::Float32x4, VK_FORMAT_R32G32B32A32_SFLOAT}};

        inline static std::map<VertexStepMode, VkVertexInputRate> m_vertexStepModeMap = {
            {VertexStepMode::Vertex, VK_VERTEX_INPUT_RATE_VERTEX}};

    public:

        /// @brief Creates an array of @see VkVertexInputBindingDescription
        /// @param descriptors The buffer layout descriptors.
        /// @param outVertexInputBindingDescriptions The array of @see VkVertexInputBindingDescription that will be filled.
        /// @param outVertexInputAttributeDescriptions The array of @see VkVertexInputAttributeDescription that will be filled.
        /// @return The created array of @see VkVertexInputBindingDescription
        /// @note outVertexInputAttributeDescriptions is here for the sake of simplicity.
        static void Create(
            const std::vector<BufferLayoutDescriptor> &descriptors, 
            std::vector<VkVertexInputBindingDescription> &outVertexInputBindingDescriptions, 
            std::vector<VkVertexInputAttributeDescription> &outVertexInputAttributeDescriptions);
    };
}

#endif // !BNS_WEBGPU_BUFFER_LAYOUT_UTIL_HPP