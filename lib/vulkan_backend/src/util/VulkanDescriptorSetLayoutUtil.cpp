#if USE_VULKAN

#include "util/VulkanDescriptorSetLayoutUtil.hpp"
#include <string>
#include <stdexcept>
#include "Types.hpp"

namespace bns
{
    VkDescriptorSetLayout VulkanDescriptorSetLayoutUtil::Create(const VkDevice &device, const VkDescriptorSetLayoutBinding &binding)
    {
        VkDescriptorSetLayoutCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        createInfo.bindingCount = 1;
        createInfo.pBindings = &binding;

        VkDescriptorSetLayout descriptorSetLayout;
        if (vkCreateDescriptorSetLayout(device, &createInfo, nullptr, &descriptorSetLayout) != VK_SUCCESS)
        {
            std::string msg = "VulkanDescriptorSetLayoutUtil::Create: Failed to create descriptor set layout";
            LOG("%s", msg.c_str());
            BREAKPOINT();
            throw std::runtime_error(msg);
        }

        return descriptorSetLayout;
    }

    VkDescriptorSetLayout VulkanDescriptorSetLayoutUtil::Create(const VkDevice &device, const std::vector<VkDescriptorSetLayoutBinding> &bindings)
    {
        VkDescriptorSetLayoutCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        createInfo.bindingCount = static_cast<u32>(bindings.size());
        createInfo.pBindings = bindings.data();

        VkDescriptorSetLayout descriptorSetLayout;
        if (vkCreateDescriptorSetLayout(device, &createInfo, nullptr, &descriptorSetLayout) != VK_SUCCESS)
        {
            std::string msg = "VulkanDescriptorSetLayoutUtil::Create: Failed to create descriptor set layout";
            LOG("%s", msg.c_str());
            BREAKPOINT();
            throw std::runtime_error(msg);
        }

        return descriptorSetLayout;
    }

    void VulkanDescriptorSetLayoutUtil::Destroy(const VkDevice &device, const VkDescriptorSetLayout &descriptorSetLayout)
    {
        vkDestroyDescriptorSetLayout(device, descriptorSetLayout, nullptr);
    }
}

#endif