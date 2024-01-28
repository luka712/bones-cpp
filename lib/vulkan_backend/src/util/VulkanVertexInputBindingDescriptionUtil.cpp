#if USE_VULKAN

#include "util/VulkanVertexInputBindingDescriptionUtil.hpp"
#include <stdexcept>
#include "Types.hpp"
#include <string>

namespace bns
{
    void VulkanVertexInputBindingDescriptionUtil::Create(const std::vector<BufferLayoutDescriptor> &descriptors,
                                                         std::vector<VkVertexInputBindingDescription> &outVertexInputBindingDescriptions,
                                                         std::vector<VkVertexInputAttributeDescription> &outVertexInputAttributeDescriptions)
    {
        if (outVertexInputBindingDescriptions.size() != 0)
        {
            std::string message = "outVertexInputBindingDescriptions must be empty";
            LOG(message);
            BREAKPOINT();
            throw std::runtime_error(message);
        }

        if (outVertexInputAttributeDescriptions.size() != 0)
        {
            std::string message = "outVertexInputAttributeDescriptions must be empty";
            LOG(message);
            BREAKPOINT();
            throw std::runtime_error(message);
        }

        size_t i = 0;
        for (const BufferLayoutDescriptor &desc : descriptors)
        {
            // Create layout
            VkVertexInputBindingDescription bufferLayout = {};
            bufferLayout.binding = i;
            bufferLayout.stride = desc.Stride;
            bufferLayout.inputRate = VulkanVertexInputBindingDescriptionUtil::m_vertexStepModeMap[desc.Step];

            outVertexInputBindingDescriptions.push_back(bufferLayout);


            // Create attributes
            for (const BufferLayoutAttributeDescriptor &attribute : desc.Attributes)
            {
                VkVertexInputAttributeDescription attributeDescription = {};
                attributeDescription.binding = i;
                attributeDescription.location = attribute.ShaderLocation;
                attributeDescription.format = VulkanVertexInputBindingDescriptionUtil::m_vertexFormatMap[attribute.Format];
                attributeDescription.offset = attribute.Offset;

                outVertexInputAttributeDescriptions.push_back(attributeDescription);
            }

            i++;
        }
    }
}

#endif