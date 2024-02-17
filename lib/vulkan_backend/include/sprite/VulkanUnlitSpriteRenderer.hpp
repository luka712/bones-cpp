#if USE_VULKAN

#ifndef BNS_VULKAN_UNLIT_SPRITE_RENDERER_HPP

#define BNS_VULKAN_UNLIT_SPRITE_RENDERER_HPP

#include "sprite/bns_sprite_renderer.hpp"
#include "sprite/VulkanUnlitSpritePipeline.hpp"
#include <map>
#include <stack>
#include "renderer/Vulkanbns_renderer.hpp"

namespace bns
{
    /**
     * @brief The Vulkan implementation of sprite renderer.
     */
    class VulkanUnlitSpriteRenderer final : public SpriteRenderer
    {
    private:
        /// @brief The renderer.
        VulkanRenderer *m_renderer;

        /// @brief The device.
        VkDevice m_device;

        /// @brief The index buffer.
        VkBuffer m_indexBuffer;

        /// @brief The index buffer memory.
        VkDeviceMemory m_indexBufferMemory;

        /// @brief The projection view matrix buffer.
        VkBuffer m_projectionViewMatrixBuffer;

        /// @brief The projection view matrix buffer memory.
        VkDeviceMemory m_projectionViewMatrixBufferMemory;

        /// @brief The brightness threshold buffer.
        VkBuffer m_brightnessThresholdBuffer;

        /// @brief The brightness threshold buffer memory.
        VkDeviceMemory m_brightnessThresholdBufferMemory;

        /// @brief All the allocated pipelines per texture. Pop from this pipeline to current draw pipelines.
        /// At the end of frame, push back to this pipeline from current draw pipelines.
        std::map<u32, std::stack<VulkanUnlitSpritePipeline *>> m_allocatedPipelines;

        /// @brief The current draw pipelines per texture. At the end of frame pop from this pipeline to allocated pipelines.
        /// If there is no allocated pipeline, create a new one and push it here.
        std::map<u32, std::stack<VulkanUnlitSpritePipeline *>> m_currentDrawPipelines;

        /// @brief The stack of vertex buffers and device memory.
        /// For each vertex buffer, there is a device memory associated with it.
        std::stack<std::pair<VkBuffer, VkDeviceMemory>> m_vertexBufferDeviceMemoryStack;

        /// @brief Setup of the index buffer.
        void SetupIndexBuffer();

        /// @brief Gets or creates a pipeline for the texture.
        /// Creation is handled internally, so just get reference.
        VulkanUnlitSpritePipeline &GetPipeline(VulkanTexture2D *texture);

    public:
        /// @brief The default constructor.
        VulkanUnlitSpriteRenderer(Renderer *m_renderer);

        void Initialize() override;

        void BeginFrame() override;

        void Draw(Texture2D *texture,
                  const Rect &drawRect,
                  const Rect &sourceRect,
                  const Color &tintColor,
                  f32 rotationInRadians, const Vec2f &rotationOrigin) override;

        void DrawString(SpriteFont *font,
                        const std::string &text,
                        const Vec2f &position,
                        const Color &color,
                        f32 scale) override;

        void EndFrame() override;
    };
}

#endif

#endif