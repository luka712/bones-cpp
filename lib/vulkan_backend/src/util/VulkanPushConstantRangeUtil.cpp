#if USE_VULKAN 

#include "util/VulkanPushConstantRangeUtil.hpp"

namespace bns
{
    VkPushConstantRange VulkanPushConstantRangeUtil::Create(VkShaderStageFlags stageFlags, u32 offset, u32 size)
    {
        VkPushConstantRange pushConstantRange{};
        pushConstantRange.stageFlags = stageFlags;
        pushConstantRange.offset = offset;
        pushConstantRange.size = size;

        return pushConstantRange;
    }
} // namespace bns

#endif 