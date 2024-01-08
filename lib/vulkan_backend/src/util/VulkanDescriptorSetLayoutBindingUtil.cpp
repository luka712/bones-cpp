#if USE_VULKAN

#include "util/VulkanDescriptorSetLayoutBindingUtil.hpp"
#include "Types.hpp"
#include <string>
#include <stdexcept>

namespace bns
{
    VkShaderStageFlags VulkanDescriptorSetLayoutBindingUtil::GetShaderStageFlag(ShaderType shaderType)
    {
        switch (shaderType)
        {
        case ShaderType::Vertex:
            return VK_SHADER_STAGE_VERTEX_BIT;
        case ShaderType::Fragment:
            return VK_SHADER_STAGE_FRAGMENT_BIT;
        case ShaderType::Compute:
            return VK_SHADER_STAGE_COMPUTE_BIT;
        case ShaderType::Geometry:
            return VK_SHADER_STAGE_GEOMETRY_BIT;
        default:
            std::string msg = "VulkanDescriptorSetLayoutBindingUtil::GetShaderStageFlags: Invalid shader type";
            LOG("%s", msg.c_str());
            BREAKPOINT();
            throw std::runtime_error(msg);
        }
    }

    VkDescriptorType VulkanDescriptorSetLayoutBindingUtil::GetDescriptorType(BindingType bufferType)
    {
        switch (bufferType)
        {
        case BindingType::Uniform:
            return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        case BindingType::CombinedTextureSampler:
            return VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        default:
            std::string msg = "VulkanDescriptorSetLayoutBindingUtil::GetDescriptorType: Invalid binding type";
            LOG("%s", msg.c_str());
            BREAKPOINT();
            throw std::runtime_error(msg);
        }
    }

    VkDescriptorSetLayoutBinding VulkanDescriptorSetLayoutBindingUtil::Create(BindingType bindingType, ShaderType shader, u32 binding)
    {

        VkShaderStageFlags stageFlag = GetShaderStageFlag(shader);
        VkDescriptorType descriptorType = GetDescriptorType(bindingType);

        VkDescriptorSetLayoutBinding layoutBinding = {};

        // The binding number that this layout binding will be bound to in the shader stage specified below. layout(binding= {binding})
        layoutBinding.binding = binding;

        // vertex, uniform, storage, index...
        layoutBinding.descriptorType = descriptorType;

        // how many descriptors are in the binding. There can be for example multiple matrices in a single binding.
        layoutBinding.descriptorCount = 1;

        // vertex, fragment, compute, geometry...
        layoutBinding.stageFlags = stageFlag;

        layoutBinding.pImmutableSamplers = nullptr; // Optional

        return layoutBinding;
    }

    VkDescriptorSetLayoutBinding VulkanDescriptorSetLayoutBindingUtil::CreateUniformForVertexStage(u32 binding)
    {
        return Create(BindingType::Uniform, ShaderType::Vertex, binding);
    }

    VkDescriptorSetLayoutBinding VulkanDescriptorSetLayoutBindingUtil::CreateUniformForFragmentStage(u32 binding)
    {
        return Create(BindingType::Uniform, ShaderType::Fragment, binding);
    }

    VkDescriptorSetLayoutBinding VulkanDescriptorSetLayoutBindingUtil::CreateTextureForFragmentStage(u32 binding)
    {
        return Create(BindingType::CombinedTextureSampler, ShaderType::Fragment, binding);
    }
}

#endif