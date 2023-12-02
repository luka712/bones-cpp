#include "util/VulkanShaderModuleUtil.hpp"
#include "Types.hpp"
#include <stdexcept>
#include <string>

#if USE_VULKAN

namespace bns
{
    VkShaderModule VulkanShaderModuleUtil::CreateFromSpirV(VkDevice device, const std::vector<char>& code)
    {
        VkShaderModuleCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = code.size();
        createInfo.pCode = reinterpret_cast<const u32*>(code.data());

        VkShaderModule shaderModule;
        if (vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS)
        {
            std::string msg = "VulkanShaderModuleUtil::CreateFromSpirV: Failed to create shader module.";
            LOG("%s", msg.c_str());
            BREAKPOINT();
            throw std::runtime_error(msg);
        }

        return shaderModule;
    }

    void VulkanShaderModuleUtil::Destroy(VkDevice device, VkShaderModule shaderModule)
    {
        vkDestroyShaderModule(device, shaderModule, nullptr);
    }

} // namespace bns

#endif 