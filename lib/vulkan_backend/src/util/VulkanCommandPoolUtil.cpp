#if USE_VULKAN

#include "util/VulkanCommandPoolUtil.hpp"
#include <string>
#include <stdexcept>

namespace bns
{
	VkCommandPool VulkanCommandPoolUtil::Create(VkDevice device, u32 queueFamilyIndex, VkCommandPoolCreateFlags flags)
	{
		VkCommandPoolCreateInfo poolInfo = {};
		poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		poolInfo.queueFamilyIndex = queueFamilyIndex;
		poolInfo.flags = flags;

		VkCommandPool commandPool;
		if (vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool) != VK_SUCCESS)
		{
			std::string msg = "VulkanCommandPoolUtil::Create: failed to create command pool!";
			LOG(msg);
			BREAKPOINT();
			throw std::runtime_error(msg);
		}

		return commandPool;
	}

	void VulkanCommandPoolUtil::Destroy(VkDevice device, VkCommandPool commandPool)
	{
		vkDestroyCommandPool(device, commandPool, nullptr);
	}
} // namespace bns

#endif 