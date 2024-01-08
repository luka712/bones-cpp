#if USE_VULKAN

#define VULKAN_DESCRIPTOR_SET_LAYOUT_BINDING_UTIL_HPP

#include "Types.hpp"
#include "BnsVulkan.hpp"
#include <vector>
#include <map>
#include "RenderingBackendTypes.hpp"

namespace bns
{
    /// @brief Utility class for creating @ref VkDescriptorSetLayoutBinding structs
    /// @note VulkanDescriptorSetLayoutBinding is similar to WGPUBindGroupLayoutEntry
    class VulkanDescriptorSetLayoutBindingUtil final
    {
    private:
        /// @brief Gets the shader stage flag from the shader type.
        /// @param shaderType The shader type.
        /// @return The shader stage flag.
        static VkShaderStageFlags GetShaderStageFlag(ShaderType shaderType);

        /// @brief Gets the descriptor type from the buffer type.
        /// @param bindingType The buffer type.
        /// @return The descriptor type.
        static VkDescriptorType GetDescriptorType(BindingType bindingType);

    public:
        /// @brief Creates a @ref VkDescriptorSetLayoutBinding. This describes the binding of a descriptor to a shader.
        /// @param bindingType The type of the binding.
        /// @param shader The shader stage that this layout binding will be bound to.
        /// @param binding The binding number that this layout binding will be bound to in the shader stage specified below. layout(binding= {binding})
        /// @return The created @ref VkDescriptorSetLayoutBinding
        static VkDescriptorSetLayoutBinding Create(BindingType bindingType, ShaderType shader, u32 binding);

        /// @brief Creates a @ref VkDescriptorSetLayoutBinding for a uniform buffer for the vertex stage.
        /// @param binding The binding number that this layout binding will be bound to in the shader stage specified below.
        /// @return The created @ref VkDescriptorSetLayoutBinding
        /// @note In glsl this is layout(binding = {binding})
        static VkDescriptorSetLayoutBinding CreateUniformForVertexStage(u32 binding);

        /// @brief Creates a @ref VkDescriptorSetLayoutBinding for a uniform buffer for the fragment stage.
        /// @param binding The binding number that this layout binding will be bound to in the shader stage specified below.
        /// @return The created @ref VkDescriptorSetLayoutBinding
        /// @note In glsl this is layout(binding = {binding})
        static VkDescriptorSetLayoutBinding CreateUniformForFragmentStage(u32 binding);

        /// @brief Creates a @ref VkDescriptorSetLayoutBinding for a texture for the fragment stage.
        /// @param binding The binding number that this layout binding will be bound to in the shader stage specified below. layout(binding= {binding})
        /// @return The created @ref VkDescriptorSetLayoutBinding
        static VkDescriptorSetLayoutBinding CreateTextureForFragmentStage(u32 binding);
    };
}

#endif