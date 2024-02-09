#if USE_VULKAN

#include "util/VulkanPipelineRasterizationStateCreateInfoUtil.hpp"
#include <stdexcept>
#include "bns_types.hpp"
#include <string>

namespace bns 
{
    VkPipelineRasterizationStateCreateInfo VulkanPipelineRasterizationStateCreateInfoUtil::Create(FrontFace frontFace, CullMode cullMode)
    {
        VkPipelineRasterizationStateCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        createInfo.depthClampEnable = VK_FALSE; // If true, fragments that are beyond the near and far planes are clamped to them as opposed to discarding them. Useful in shadow maps
        createInfo.rasterizerDiscardEnable = VK_FALSE; // If true, geometry never passes through the rasterizer stage. This basically disables any output to the framebuffer
        createInfo.polygonMode = VK_POLYGON_MODE_FILL; // How to handle filling points between vertices
        createInfo.lineWidth = 1.0f; // How thick lines should be when drawn
        createInfo.cullMode = GetCullModeFlags(cullMode); // Which face of a triangle to cull
        createInfo.frontFace = GetFrontFace(frontFace); // The winding order for faces to be considered front-facing and thus, culled
        createInfo.depthBiasEnable = VK_FALSE; // If true, then fragments that are closer to the camera will have a higher depth value
        createInfo.depthBiasConstantFactor = 0.0f; // The constant factor by which to bias fragment depth values
        createInfo.depthBiasClamp = 0.0f; // The maximum (or minimum) depth bias of a fragment
        createInfo.depthBiasSlopeFactor = 0.0f; // The slope factor by which to bias fragment depth values

        return createInfo;
    }

    VkCullModeFlags VulkanPipelineRasterizationStateCreateInfoUtil::GetCullModeFlags(const CullMode &cullMode) 
    {
        switch (cullMode)
        {
        case CullMode::None:
            return VK_CULL_MODE_NONE;
        case CullMode::Front:
            return VK_CULL_MODE_FRONT_BIT;
        case CullMode::Back:
            return VK_CULL_MODE_BACK_BIT;
        case CullMode::FrontAndBack:
            return VK_CULL_MODE_FRONT_AND_BACK;
        default:
            std::string msg = "VulkanPipelineRasterizationStateCreateInfoUtil::GetCullModeFlags: Invalid CullMode: " + std::to_string(static_cast<int>(cullMode));
           LOG(msg);
            BREAKPOINT();
            throw std::runtime_error(msg);
        }
    }

    VkFrontFace VulkanPipelineRasterizationStateCreateInfoUtil::GetFrontFace(const FrontFace &frontFace) 
    {
        switch (frontFace)
        {
        case FrontFace::Clockwise:
            return VK_FRONT_FACE_CLOCKWISE;
        case FrontFace::CounterClockwise:
            return VK_FRONT_FACE_COUNTER_CLOCKWISE;
        default:
            std::string msg = "VulkanPipelineRasterizationStateCreateInfoUtil::GetFrontFace: Invalid FrontFace: " + std::to_string(static_cast<int>(frontFace));
           LOG(msg);
            BREAKPOINT();
            throw std::runtime_error(msg);
        }
    }
}

#endif 