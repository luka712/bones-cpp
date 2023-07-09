#pragma once

#ifndef BNS_RENDERER_METAL_HPP

#define BNS_RENDERER_METAL_HPP

#include "Metal/Metal.hpp"
#include "data/Vec2.hpp"
#include "data/Color.hpp"

namespace bns
{
    class MetalRenderer
    {
    private:
        /**
         * @brief MetalLayer is a class in Apple's Metal
         * framework that enables seamless integration of Metal rendering capabilities into a Core Animation layer hierarchy.
         */
        CA::MetalLayer *m_metalLayer;

        /**
         * @brief Device is a class in Apple's Metal framework that represents a GPU device.
         * It is similar to Adapter/Device in the WebGPU API.
         * It is similar to a physical device in Vulkan.
         * It is similar to an adapter in DirectX.
        */
        MTL::Device *m_device;

        /**
         * @brief MetalDrawable is a protocol in the Metal framework that represents a drawable texture,
         * which can be used as a rendering destination for Metal commands.
         * It enables integration between Metal and higher-level frameworks like MetalKit for rendering graphics.
         * It is similar to Texture in the WebGPU API.
         * It is similar to a frame buffer in Vulkan.
         * It is similar to a back buffer in DirectX.
         */
        CA::MetalDrawable *m_currentDrawable;

        MTL::RenderCommandEncoder *m_renderCommandEncoder;
        MTL::CommandBuffer *m_commandBuffer;
        MTL::RenderPipelineState *m_renderPipelineState;
        MTL::Buffer *m_positionBuffer;
        MTL::Buffer *m_colorsBuffer;

        Vec2f m_bufferSize;

        void Resize();

    public:
        Color ClearColor;

        MetalRenderer();
        void Initialize(CA::MetalLayer *metalLayer);
        void BeginDraw();
        void EndDraw();
    };
} // namespace BNS

#endif // !BNS_RENDERER_METAL_HPP