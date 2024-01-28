#if USE_VULKAN

#include "util/VulkanSemaphoreUtil.hpp"
#include <string>
#include "Types.hpp"
#include <stdexcept>

namespace bns
{
    VkSemaphore VulkanSemaphoreUtil::Create(VkDevice device)
    {
        VkSemaphoreCreateInfo semaphoreCreateInfo = {};
        semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

        VkSemaphore semaphore;
        if (vkCreateSemaphore(device, &semaphoreCreateInfo, nullptr, &semaphore) != VK_SUCCESS)
        {
            std::string msg = "VulkanSemaphoreUtil::Create: Failed to create semaphore";
           LOG(msg);
            BREAKPOINT();
            throw std::runtime_error(msg);
        }

        return semaphore;
    }

    void VulkanSemaphoreUtil::Destroy(VkDevice device, VkSemaphore semaphore)
    {
        vkDestroySemaphore(device, semaphore, nullptr);
    }
}

#endif