#include "sprite/wgpu/WebGPUSpriteRenderer.hpp"
#include "util/wgpu/WebGPUBufferUtil.hpp"
#include "Constants.hpp"
#include "Framework.hpp"

namespace bns
{
    WebGPUSpriteRenderer::WebGPUSpriteRenderer(const Framework &framework)
        : m_framework(framework)
    {
    }

    void WebGPUSpriteRenderer::SetupIndexBuffer()
    {
        std::vector<u16> data(6 * SPRITE_RENDERER_MAX_SPRITES_PER_DRAW);

        for (size_t i = 0; i < SPRITE_RENDERER_MAX_SPRITES_PER_DRAW; i++)
        {
            // t1
            data[i * 6 + 0] = i * 4 + 0;
            data[i * 6 + 1] = i * 4 + 1;
            data[i * 6 + 2] = i * 4 + 2;

            // t2
            data[i * 6 + 3] = i * 4 + 2;
            data[i * 6 + 4] = i * 4 + 3;
            data[i * 6 + 5] = i * 4 + 0;
        }

        m_indexBuffer = WebGPUBufferUtil::CreateIndexBuffer(m_device, data, "SpriteRendererIndexBuffer");
    }

    WebGPUSpritePipeline &WebGPUSpriteRenderer::GetPipeline(WebGPUTexture2D *texture)
    {
        u32 textureId = texture->GetID();

        // if not found allocated new vector array for texture name key. No need to check both, they should have same keys.
        if (m_currentDrawPipelines.count(textureId) == 0)
        {
            // first check if there is one in allocated pipelines. If so get it from there
            if (!m_allocatedPipelines[textureId].empty())
            {
                WebGPUSpritePipeline *pipeline = m_allocatedPipelines[textureId].top();
                m_allocatedPipelines[textureId].pop();
                m_currentDrawPipelines[textureId].push(pipeline);
                return *pipeline;
            }

            // if not found, we are sure that there is no pipeline, create one and push it to current draw pipelines.
            WebGPUSpritePipeline *pipeline = WebGPUSpritePipeline::Create(m_device, texture, m_projectionViewMatrixBuffer);
            m_currentDrawPipelines[textureId].push(pipeline);
            m_allocatedPipelines[textureId].push(pipeline);
            return *pipeline;
        }

        auto topPipelineRef = m_currentDrawPipelines[textureId].top();

        // if pipeline is full, allocate a new pipeline.
        if (topPipelineRef->InstanceIndex == SPRITE_RENDERER_MAX_SPRITES_PER_DRAW)
        {
            // if there is no allocated pipeline, create one and push it to current draw pipelines.
            // return then new pipeline.
            if (m_allocatedPipelines[textureId].empty())
            {
                WebGPUSpritePipeline *pipeline = WebGPUSpritePipeline::Create(m_device, texture, m_projectionViewMatrixBuffer);
                m_currentDrawPipelines[textureId].push(pipeline);
                m_allocatedPipelines[textureId].push(pipeline);
                return *pipeline;
            }

            WebGPUSpritePipeline *pipeline = m_allocatedPipelines[textureId].top();
            m_allocatedPipelines[textureId].pop();
            m_currentDrawPipelines[textureId].push(pipeline);
            return *pipeline;
        }

        return *topPipelineRef;
    }

    void WebGPUSpriteRenderer::Initialize()
    {
        // setup camera buffer
        m_device = m_framework.Context.WebGPUDevice;
        m_projectionViewMatrixBuffer = WebGPUBufferUtil::CreateUniformBuffer(m_device, sizeof(Mat4x4f), "SpriteRendererCameraBuffer");

        // setup camera
        auto size = m_framework.GetWindowManager().GetWindowSize();
        m_camera = SpriteRendererCamera(size.X, size.Y);

        SetupIndexBuffer();
    }

    void WebGPUSpriteRenderer::BeginFrame()
    {
        m_camera.Update(0.0f);

        WGPUQueue queue = wgpuDeviceGetQueue(m_device);

        // write camera buffer to gpu
        wgpuQueueWriteBuffer(queue, m_projectionViewMatrixBuffer, 0, &m_camera.ProjectionViewMatrix, sizeof(Mat4x4f));

        // empty current draw pipelines
        for (auto keyValuePair : m_currentDrawPipelines)
        {
            std::stack<WebGPUSpritePipeline *> &pipelineStack = keyValuePair.second;
            while (!pipelineStack.empty())
            {
                pipelineStack.pop();
            }
        }
    }

    void WebGPUSpriteRenderer::Draw(Texture2D *texture, const Rect &drawRect, const Rect &sourceRect,
                                    const Color &tintColor, f32 rotationInRadians, const Vec2f &rotationOrigin)
    {
        WebGPUTexture2D *wgpuTexture = static_cast<WebGPUTexture2D *>(texture);
        WebGPUSpritePipeline &pipeline = GetPipeline(wgpuTexture);

        u32 i = pipeline.InstanceIndex * FLOATS_PER_INSTANCE;

        auto d = pipeline.DataArray;

        Vec2f topLeft = Vec2f(drawRect.X, drawRect.Y);
        Vec2f topRight = Vec2f(drawRect.X + drawRect.Width, drawRect.Y);
        Vec2f bottomRight = Vec2f(drawRect.X + drawRect.Width, drawRect.Y + drawRect.Height);
        Vec2f bottomLeft = Vec2f(drawRect.X, drawRect.Y + drawRect.Height);

        // perform rotation
        if (rotationInRadians != 0)
        {
            Vec2f rotationOriginOffset = Vec2f(
                topLeft.X + drawRect.Width * rotationOrigin.X,
                topLeft.Y + drawRect.Height * rotationOrigin.Y);

            topLeft.RotateAroundPoint(rotationOriginOffset, rotationInRadians);
            topRight.RotateAroundPoint(rotationOriginOffset, rotationInRadians);
            bottomRight.RotateAroundPoint(rotationOriginOffset, rotationInRadians);
            bottomLeft.RotateAroundPoint(rotationOriginOffset, rotationInRadians);
        }

        // find texture coords
        f32 u0 = static_cast<float>(sourceRect.X) / static_cast<float>(texture->GetWidth());
        f32 v0 = static_cast<float>(sourceRect.Y) / static_cast<float>(texture->GetHeight());
        f32 u1 = static_cast<float>(sourceRect.X + sourceRect.Width) / static_cast<float>(texture->GetWidth());
        f32 v1 = static_cast<float>(sourceRect.Y + sourceRect.Height) / static_cast<float>(texture->GetHeight());

        // t1
        d[i + 0] = topLeft.X;
        d[i + 1] = topLeft.Y;
        d[i + 2] = 0.0f;        // z
        d[i + 3] = u0;          // u
        d[i + 4] = v0;          // v
        d[i + 5] = tintColor.R; // r
        d[i + 6] = tintColor.G; // g
        d[i + 7] = tintColor.B; // b
        d[i + 8] = tintColor.A; // a

        // t2
        d[i + 9] = topRight.X;
        d[i + 10] = topRight.Y;
        d[i + 11] = 0.0f;        // z
        d[i + 12] = u1;          // u
        d[i + 13] = v0;          // v
        d[i + 14] = tintColor.R; // r
        d[i + 15] = tintColor.G; // g
        d[i + 16] = tintColor.B; // b
        d[i + 17] = tintColor.A; // a

        // t3
        d[i + 18] = bottomRight.X;
        d[i + 19] = bottomRight.Y;
        d[i + 20] = 0.0f;        // z
        d[i + 21] = u1;          // u
        d[i + 22] = v1;          // v
        d[i + 23] = tintColor.R; // r
        d[i + 24] = tintColor.G; // g
        d[i + 25] = tintColor.B; // b
        d[i + 26] = tintColor.A; // a

        // t4
        d[i + 27] = bottomLeft.X;
        d[i + 28] = bottomLeft.Y;
        d[i + 29] = 0.0f;        // z
        d[i + 30] = u0;          // u
        d[i + 31] = v1;          // v
        d[i + 32] = tintColor.R; // r
        d[i + 33] = tintColor.G; // g
        d[i + 34] = tintColor.B; // b
        d[i + 35] = tintColor.A; // a

        pipeline.InstanceIndex++;
    }

    void WebGPUSpriteRenderer::DrawString(SpriteFont *font, const std::string &text, const Vec2f &position,
                                          const Color &color, const f32 scale)
    {
        
    }

    void WebGPUSpriteRenderer::EndFrame()
    {
        WGPURenderPassEncoder renderPass = m_framework.Context.CurrentWebGPURenderPassEncoder;
        WGPUQueue queue = wgpuDeviceGetQueue(m_device);
        
        std::stack<WGPUBuffer> tempVertexBufferStack;

        // go through each key
        for (auto keyValuePair : m_currentDrawPipelines)
        {
            // go through each pipeline
            u32 textureId = keyValuePair.first;
            std::stack<WebGPUSpritePipeline *> &pipelineStack = keyValuePair.second;

            while (!pipelineStack.empty())
            {
                // get the pipeline, pop it from stack and push it to allocated stack
                WebGPUSpritePipeline *spritePipeline = pipelineStack.top();
                pipelineStack.pop();
                m_allocatedPipelines[textureId].push(spritePipeline);

                auto pipeline = spritePipeline->GetPipeline();
                auto projectionViewBindGroup = spritePipeline->GetProjectionViewBindGroup();
                auto textureBindGroup = spritePipeline->GetTextureBindGroup();

                // allocate or get vertex buffer.
                WGPUBuffer vertexBuffer;
                if (m_vertexBufferStack.empty())
                {
                    size_t byteSize = SPRITE_RENDERER_MAX_SPRITES_PER_DRAW * FLOATS_PER_INSTANCE * sizeof(float);
                    vertexBuffer = WebGPUBufferUtil::CreateVertexBuffer(m_device, byteSize, "SpriteVertexBuffer");
                }
                else
                {
                    vertexBuffer = m_vertexBufferStack.top();
                    m_vertexBufferStack.pop();
                }

                // push to temp stack
                tempVertexBufferStack.push(vertexBuffer);

                size_t byteSize = SPRITE_RENDERER_MAX_SPRITES_PER_DRAW * FLOATS_PER_INSTANCE * sizeof(f32);
                wgpuQueueWriteBuffer(queue, vertexBuffer, 0, spritePipeline->DataArray, byteSize);

                // set pipeline
                wgpuRenderPassEncoderSetPipeline(renderPass, pipeline);

                // set bind groups
                wgpuRenderPassEncoderSetBindGroup(renderPass, 0, projectionViewBindGroup, 0, 0);
                wgpuRenderPassEncoderSetBindGroup(renderPass, 1, textureBindGroup, 0, 0);

                // set vertex index buffer
                wgpuRenderPassEncoderSetVertexBuffer(renderPass, 0, vertexBuffer, 0, 0);
                wgpuRenderPassEncoderSetIndexBuffer(renderPass, m_indexBuffer, WGPUIndexFormat_Uint16, 0,
                                                    6 * SPRITE_RENDERER_MAX_SPRITES_PER_DRAW * sizeof(u16));

                // draw
                wgpuRenderPassEncoderPushDebugGroup(renderPass, "Draw Indexed");
                wgpuRenderPassEncoderDrawIndexed(renderPass, spritePipeline->InstanceIndex * 6, 1, 0, 0, 0);
                wgpuRenderPassEncoderPopDebugGroup(renderPass);


                spritePipeline->InstanceIndex = 0;
            }
        }

        // return vertex buffers to stack
        while (!tempVertexBufferStack.empty())
        {
            m_vertexBufferStack.push(tempVertexBufferStack.top());
            tempVertexBufferStack.pop();
        }
    }
}
