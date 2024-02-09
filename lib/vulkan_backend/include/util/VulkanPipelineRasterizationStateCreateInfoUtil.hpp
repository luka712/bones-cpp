#if USE_VULKAN

#ifndef BNS_VULKAN_PIPELINE_RASTERIZATION_STATE_CREATE_INFO_UTIL_HPP

#define BNS_VULKAN_PIPELINE_RASTERIZATION_STATE_CREATE_INFO_UTIL_HPP

#include "BnsVulkan.hpp"
#include "bns_rendering_backend_types.hpp"

namespace bns
{
    /// @brief  The util class for working with @ref VkPipelineRasterizationStateCreateInfo
    class VulkanPipelineRasterizationStateCreateInfoUtil final
    {
    private:
        /// @brief Get the @ref VkCUllModeFlags from the given @ref CullMode.
        /// @param cullMode The @ref CullMode to convert.
        static VkCullModeFlags GetCullModeFlags(const CullMode &cullMode);

        /// @brief Get the @ref VkFrontFace from the given @ref FrontFace.
        /// @param frontFace The @ref FrontFace to convert.
        static VkFrontFace GetFrontFace(const FrontFace &frontFace);

    public:
        /// @brief Get the default @ref VkPipelineRasterizationStateCreateInfo.
        /// @param frontFace The @ref FrontFace to use. By default it is @ref FrontFace::CounterClockwise.
        /// @param cullMode The @ref CullMode to use. By default it is @ref CullMode::Back.
        /// @return The default @ref VkPipelineRasterizationStateCreateInfo
        static VkPipelineRasterizationStateCreateInfo Create(FrontFace frontFace = FrontFace::CounterClockwise, CullMode cullMode = CullMode::None);

        /// @brief Get the default @ref VkPipelineRasterizationStateCreateInfo.
        /// The default @ref FrontFace is @ref FrontFace::CounterClockwise.
        /// The default @ref CullMode is @ref CullMode::Back.
        /// @return The default @ref VkPipelineRasterizationStateCreateInfo
        static VkPipelineRasterizationStateCreateInfo Default();
    };
}

#endif

#endif