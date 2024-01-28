#include "util/VulkanShaderModuleUtil.hpp"
#include "Types.hpp"
#include <stdexcept>
#include <string>
#include "FileLoader.hpp"

#if USE_VULKAN

namespace bns
{
    VkShaderModule VulkanShaderModuleUtil::CreateFromSpirVSource(VkDevice device, const std::vector<char>& code)
    {
        VkShaderModuleCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = code.size();
        createInfo.pCode = reinterpret_cast<const u32*>(code.data());

        VkShaderModule shaderModule;
        if (vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS)
        {
            std::string msg = "VulkanShaderModuleUtil::CreateFromSpirV: Failed to create shader module.";
           LOG(msg);
            BREAKPOINT();
            throw std::runtime_error(msg);
        }

        return shaderModule;
    }

    VkShaderModule VulkanShaderModuleUtil::CreateFromSpirVFilepath(VkDevice device, std::string filepath)
    {
        FileLoader fileLoader;
        std::vector<char> code = fileLoader.LoadFileAsBinary(filepath);

        return CreateFromSpirVSource(device, code);
    }

    void VulkanShaderModuleUtil::Destroy(VkDevice device, VkShaderModule shaderModule)
    {
        vkDestroyShaderModule(device, shaderModule, nullptr);
    }

} // namespace bns

#endif 