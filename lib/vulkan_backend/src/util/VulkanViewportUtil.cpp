#if USE_VULKAN

#include "util/VulkanViewportUtil.hpp"

namespace bns
{
    VkViewport VulkanViewportUtil::Default(f32 width, f32 height)
    {
        VkViewport viewport{};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = width;
        viewport.height = height;
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;

        return viewport;
    }

    VkViewport VulkanViewportUtil::FlipY(f32 width, f32 height)
    {
        // Y flip is done in order to match OpenGL's/Metal/DX/WebGPU coordinate system.
        VkViewport viewport{};
        viewport.x = 0.0f;
        viewport.y = height;
        viewport.width = width;
        viewport.height = -height;
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;

        return viewport;
    }

    VkViewport VulkanViewportUtil::Create(VkExtent2D swapChainExtent)
    {
        return Default(static_cast<f32>(swapChainExtent.width), static_cast<f32>(swapChainExtent.height));
    }

} // namespace bns

#endif 