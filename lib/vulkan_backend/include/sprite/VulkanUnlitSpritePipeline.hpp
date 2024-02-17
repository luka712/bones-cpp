#if USE_VULKAN

#ifndef BNS_VULKAN_UNLIT_SPRITE_PIPELINE

#define BNS_VULKAN_UNLIT_SPRITE_PIPELINE

#include "Constants.hpp"
#include "texture/VulkanTexture2D.hpp"
#include <vector>
#include "loaders/bns_file_loader.hpp"

#define FLOATS_PER_VERTEX 9
#define FLOATS_PER_INSTANCE (4 * FLOATS_PER_VERTEX)

namespace bns
{
    /// @brief The unlit sprite pipeline
    class VulkanUnlitSpritePipeline final
    {
    private:
        VkPipeline m_pipeline;
        VkPipelineLayout m_pipelineLayout;

        // The descriptor pool
        VkDescriptorPool m_descriptorPool;

        // We only need one descriptor set per frame
        std::vector<VkDescriptorSet> m_descriptorSets;

        // WGPUBindGroup m_projectionViewBindGroup;
        // WGPUBindGroup m_sourceTextureBindGroup;
        // WGPUBindGroup m_brightnessThresholdBindGroup;

        /// @brief Creates the projection view bind group layout.
        /// @param device The Vulkan device.
        /// @param projectionViewBindGroupLayout The projection view bind group layout.
        /// @param projectionViewBuffer The projection view buffer.
        /// @return The projection view bind group layout.
        // static WGPUBindGroup CreateProjectionViewBindGroup(WGPUDevice &device,
        //                                                    WGPUBindGroupLayout &projectionViewBindGroupLayout,
        //                                                    WGPUBuffer &projectionViewBuffer);

        /// @brief Creates the texture bind group.
        /// @param device The Vulkan device.
        /// @param textureBindGroupLayout The texture bind group layout.
        /// @param texture The texture.
        /// @return The texture bind group.
        // static WGPUBindGroup CreateTextureBindGroup(WGPUDevice &device,
        //                                             WGPUBindGroupLayout &textureBindGroupLayout,
        //                                             VulkanTexture2D *texture);

        /// @brief Creates the brightness threshold bind group.
        /// @param device The Vulkan device.
        /// @param brightnessThresholdBindGroupLayout The brightness threshold bind group layout.
        /// @param brightnessThresholdBuffer The brightness threshold buffer.
        /// @return The brightness threshold bind group.
        // static WGPUBindGroup CreateBrightnessThresholdBindGroup(WGPUDevice &device,
        //                                                         WGPUBindGroupLayout &brightnessThresholdBindGroupLayout,
        //                                                         WGPUBuffer &brightnessThresholdBuffer);

    public:
        VulkanUnlitSpritePipeline::VulkanUnlitSpritePipeline(VkPipeline pipeline, 
        VkPipelineLayout pipelineLayout, 
        VkDescriptorPool descriptorPool,
        std::vector<VkDescriptorSet> descriptorSets)
        {
            m_pipeline = pipeline;
            m_pipelineLayout = pipelineLayout;
            m_descriptorSets = descriptorSets;
            m_descriptorPool = descriptorPool;
            InstanceIndex = 0;
        }

        /// @brief The constructor.
        /// @param device The Vulkan device.
        /// @param renderPass The render pass.
        /// @param framesInFlight The frames in flight.
        /// @param texture The texture.
        /// @param projectionViewBuffer The projection view buffer.
        /// @return The unlit sprite pipeline.
        static VulkanUnlitSpritePipeline *Create(const VkDevice &device,
                                                 const VkRenderPass &renderPass,
                                                 u32 framesInFlight,
                                                 const VulkanTexture2D &texture,
                                                 const VkBuffer& projectionViewBuffer);

        /// @brief The instance index which is used to tell how many instances are in buffer and to be drawn.
        u32 InstanceIndex;

        /// @brief The vertex buffer data.
        f32 DataArray[SPRITE_RENDERER_MAX_SPRITES_PER_DRAW * FLOATS_PER_INSTANCE];

        /// @brief Gets the pipeline
        inline const VkPipeline &GetPipeline() const { return m_pipeline; }

        /// @brief Gets the pipeline layout
        inline const VkPipelineLayout &GetPipelineLayout() const { return m_pipelineLayout; }

        /// @brief Gets the descriptor pool
        inline const VkDescriptorPool &GetDescriptorPool() const { return m_descriptorPool; }

        /// @brief Gets the descriptor sets
        inline const std::vector<VkDescriptorSet> &GetDescriptorSets() const { return m_descriptorSets; }

        /// @brief Gets the global bind group
        // inline const WGPUBindGroup &GetProjectionViewBindGroup() const { return m_projectionViewBindGroup; }

        /// @brief Gets the texture bind group
        // inline const WGPUBindGroup &GetTextureBindGroup() const { return m_sourceTextureBindGroup; }

        /// @brief Gets the brightness threshold bind group
        // inline const WGPUBindGroup &GetBrightnessThresholdBindGroup() const { return m_brightnessThresholdBindGroup; }
    };
}

#endif

#endif