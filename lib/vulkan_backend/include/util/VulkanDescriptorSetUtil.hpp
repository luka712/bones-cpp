#if USE_VULKAN

#ifndef BNS_VULKAN_DESCRIPTOR_SET_UTIL_HPP

#define BNS_VULKAN_DESCRIPTOR_SET_UTIL_HPP

#include "BnsVulkan.hpp"
#include <vector>
#include "Types.hpp"

namespace bns
{
    /// @brief Data transfer object for updating a descriptor set
    struct VulkanUpdateDescriptorDto
    {
        VulkanUpdateDescriptorDto(
            u32 binding = 0,
            VkDescriptorType descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
            VkDescriptorBufferInfo *bufferInfo = nullptr,
            VkDescriptorImageInfo *imageInfo = nullptr);

        /// @brief The binding to update
        u32 Binding;

        /// @brief The descriptor type
        VkDescriptorType DescriptorType;

        /// @brief The buffer info. The buffer info is used as a pointer to the buffer.
        VkDescriptorBufferInfo *BufferInfo;

        /// @brief The image info. The image info is used as a pointer to the image.
        VkDescriptorImageInfo *ImageInfo;
    };

    struct VulkanDescriptorSetUtil
    {
        /// @brief Creates a @ref VkDescriptorSet
        /// @param device The device to create the descriptor set on
        /// @param descriptorPool The descriptor pool to create the descriptor set on
        /// @param descriptorSetLayouts The descriptor set layouts to create the descriptor set on
        /// @param maxFramesInFlight The max frames in flight
        /// @return The created descriptor sets
        static std::vector<VkDescriptorSet> Create(
            const VkDevice &device,
            const VkDescriptorPool &descriptorPool,
            const std::vector<VkDescriptorSetLayout> &descriptorSetLayouts,
            u32 maxFramesInFlight);

        /// @brief Updates a @ref VkDescriptorSet
        /// @param device The device to update the descriptor set on
        /// @param descriptorSet The descriptor set to update
        /// @param updateDescriptorDtos The update descriptor dtos. The hold information about the binding, descriptor type, buffer info, and image info.
        static void Update(
            const VkDevice &device,
            const VkDescriptorSet &descriptorSet,
            const std::vector<VulkanUpdateDescriptorDto>& updateDescriptorDtos);
    };
}

#endif

#endif