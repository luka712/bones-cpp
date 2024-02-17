#if USE_VULKAN

#include "sprite/VulkanUnlitbns_sprite_renderer.hpp"
#include "VulkanUtil.hpp"
#include "Constants.hpp"

namespace bns
{
    VulkanUnlitSpriteRenderer::VulkanUnlitSpriteRenderer(Renderer *m_renderer)
        : SpriteRenderer(), m_renderer(static_cast<VulkanRenderer *>(m_renderer))
    {
        BrightnessThreshold = 0.3f;
        AmbientLight.Intensity = 1.0f;
        AmbientLight.Color = Color::White();
    }

    void VulkanUnlitSpriteRenderer::SetupIndexBuffer()
    {
        std::vector<u16> data(6 * SPRITE_RENDERER_MAX_SPRITES_PER_DRAW);

        // setup indices.
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

        // create buffer with indices.
        m_indexBuffer = VulkanUtil::Buffer.CreateIndexBuffer(
            m_renderer->GetPhysicalDevice(),
            m_renderer->GetDevice(),
            data,
            &m_indexBufferMemory);
    }

    VulkanUnlitSpritePipeline &VulkanUnlitSpriteRenderer::GetPipeline(VulkanTexture2D *texture)
    {
        u32 textureId = texture->GetID();

        // if not found allocated new vector array for texture name key. No need to check both, they should have same keys.
        if (m_currentDrawPipelines.count(textureId) == 0 || m_currentDrawPipelines[textureId].empty())
        {
            // first check if there is one in allocated pipelines. If so get it from there
            if (!m_allocatedPipelines[textureId].empty())
            {
                VulkanUnlitSpritePipeline *pipeline = m_allocatedPipelines[textureId].top();
                m_allocatedPipelines[textureId].pop();
                m_currentDrawPipelines[textureId].push(pipeline);
                return *pipeline;
            }

            // if not found, we are sure that there is no pipeline, create one and push it to current draw pipelines.
            VulkanUnlitSpritePipeline *pipeline = VulkanUnlitSpritePipeline::Create(
                m_renderer->GetDevice(),
                m_renderer->GetRenderPass(),
                m_renderer->GetFramesInFlight(),
                *texture,
                m_projectionViewMatrixBuffer);



            m_currentDrawPipelines[textureId].push(pipeline);
            m_allocatedPipelines[textureId].push(pipeline);
            return *pipeline;
        }
        
        VulkanUnlitSpritePipeline* topPipelineRef = m_currentDrawPipelines[textureId].top();

        // if pipeline is full, allocate a new pipeline.
        if (topPipelineRef->InstanceIndex == SPRITE_RENDERER_MAX_SPRITES_PER_DRAW)
        {
            // if there is no allocated pipeline, create one and push it to current draw pipelines.
            // return then new pipeline.
            if (m_allocatedPipelines[textureId].empty())
            {
                VulkanUnlitSpritePipeline *pipeline = VulkanUnlitSpritePipeline::Create(
                    m_renderer->GetDevice(),
                    m_renderer->GetRenderPass(),
                    m_renderer->GetFramesInFlight(),
                    *texture,
                    m_projectionViewMatrixBuffer);

                m_currentDrawPipelines[textureId].push(pipeline);
                m_allocatedPipelines[textureId].push(pipeline);
                return *pipeline;
            }

            VulkanUnlitSpritePipeline *pipeline = m_allocatedPipelines[textureId].top();
            m_allocatedPipelines[textureId].pop();
            m_currentDrawPipelines[textureId].push(pipeline);
            return *pipeline;
        }

        return *topPipelineRef;
    }

    void VulkanUnlitSpriteRenderer::Initialize()
    {
        auto size = m_renderer->GetBufferSize();
        m_camera.Initialize(size.X, size.Y);

        // GLOBLA BUFFERS
        // setup camera buffer
        m_device = m_renderer->GetDevice();
        m_projectionViewMatrixBuffer = VulkanUtil::Buffer.CreateUniformBuffer(m_renderer->GetPhysicalDevice(),
                                                                              m_renderer->GetDevice(),
                                                                              sizeof(Mat4x4f),
                                                                              &m_projectionViewMatrixBufferMemory);

        // setup brightness threshold buffer
        m_brightnessThresholdBuffer = VulkanUtil::Buffer.CreateUniformBuffer(m_renderer->GetPhysicalDevice(),
                                                                             m_renderer->GetDevice(),
                                                                             sizeof(f32),
                                                                             &m_brightnessThresholdBufferMemory);

        SetupIndexBuffer();
    }

    void VulkanUnlitSpriteRenderer::BeginFrame()
    {
        m_camera.Update(0.0f);

        // WGPUQueue queue = wgpuDeviceGetQueue(m_device);

        // write camera buffer to gpu
        VulkanUtil::DeviceMemory.Map(m_device, m_projectionViewMatrixBufferMemory, &m_camera.ProjectionViewMatrix, sizeof(Mat4x4f));

        // Write brightness threshold buffer to gpu
        VulkanUtil::DeviceMemory.Map(m_device, m_brightnessThresholdBufferMemory, &BrightnessThreshold, sizeof(f32));

        // empty current draw pipelines
        // key pair of <u32 textureId, stack of pipelines>
        for (auto &keyValuePair : m_currentDrawPipelines)
        {
            std::stack<VulkanUnlitSpritePipeline *> &pipelineStack = keyValuePair.second;
            while (!pipelineStack.empty())
            {
                pipelineStack.pop();
            }
        }
    }

    void VulkanUnlitSpriteRenderer::Draw(Texture2D *texture, const Rect &drawRect, const Rect &sourceRect,
                                         const Color &tintColor, f32 rotationInRadians, const Vec2f &rotationOrigin)
    {
        VulkanTexture2D *vulkanTexture = static_cast<VulkanTexture2D *>(texture);
        VulkanUnlitSpritePipeline &pipeline = GetPipeline(vulkanTexture);

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
        f32 u0 = sourceRect.X / static_cast<float>(texture->GetWidth());
        f32 v0 = sourceRect.Y / static_cast<float>(texture->GetHeight());
        f32 u1 = (sourceRect.X + sourceRect.Width) / static_cast<float>(texture->GetWidth());
        f32 v1 = (sourceRect.Y + sourceRect.Height) / static_cast<float>(texture->GetHeight());

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

    void VulkanUnlitSpriteRenderer::DrawString(SpriteFont *font, const std::string &text, const Vec2f &position,
                                               const Color &tintColor, const f32 scale)
    {
        VulkanTexture2D *vulkanTexture = static_cast<VulkanTexture2D *>(font->GetTexture());

        i32 advanceX = 0;
        for (char textChar : text)
        {
            VulkanUnlitSpritePipeline &pipeline = GetPipeline(vulkanTexture);
            u32 i = pipeline.InstanceIndex * FLOATS_PER_INSTANCE;

            auto data = pipeline.DataArray;

            SpriteFontChar fontChar = font->GetChar(textChar);

            i32 x = position.X + (advanceX + fontChar.Offset.X) * scale;
            i32 y = position.Y + fontChar.Offset.Y * scale;
            i32 w = fontChar.Size.X * scale;
            i32 h = fontChar.Size.Y * scale;

            Vec2f topLeft = Vec2f(x, y);
            Vec2f topRight = Vec2f(x + w, y);
            Vec2f bottomRight = Vec2f(x + w, y + h);
            Vec2f bottomLeft = Vec2f(x, y + h);

            Vec2f a = fontChar.TextureCoords.TopLeft;
            Vec2f b = fontChar.TextureCoords.TopRight;
            Vec2f c = fontChar.TextureCoords.BottomRight;
            Vec2f d = fontChar.TextureCoords.BottomLeft;

            // t1
            data[i + 0] = topLeft.X;
            data[i + 1] = topLeft.Y;
            data[i + 2] = 0.0f;        // z
            data[i + 3] = a.X;         // u
            data[i + 4] = a.Y;         // v
            data[i + 5] = tintColor.R; // r
            data[i + 6] = tintColor.G; // g
            data[i + 7] = tintColor.B; // b
            data[i + 8] = tintColor.A; // a

            // t2
            data[i + 9] = topRight.X;
            data[i + 10] = topRight.Y;
            data[i + 11] = 0.0f;        // z
            data[i + 12] = b.X;         // u
            data[i + 13] = b.Y;         // v
            data[i + 14] = tintColor.R; // r
            data[i + 15] = tintColor.G; // g
            data[i + 16] = tintColor.B; // b
            data[i + 17] = tintColor.A; // a

            // t3
            data[i + 18] = bottomRight.X;
            data[i + 19] = bottomRight.Y;
            data[i + 20] = 0.0f;        // z
            data[i + 21] = c.X;         // u
            data[i + 22] = c.Y;         // v
            data[i + 23] = tintColor.R; // r
            data[i + 24] = tintColor.G; // g
            data[i + 25] = tintColor.B; // b
            data[i + 26] = tintColor.A; // a

            // t4
            data[i + 27] = bottomLeft.X;
            data[i + 28] = bottomLeft.Y;
            data[i + 29] = 0.0f;        // z
            data[i + 30] = d.X;         // u
            data[i + 31] = d.Y;         // v
            data[i + 32] = tintColor.R; // r
            data[i + 33] = tintColor.G; // g
            data[i + 34] = tintColor.B; // b
            data[i + 35] = tintColor.A; // a

            advanceX += fontChar.Advance;
            pipeline.InstanceIndex++;
        }
    }

    void VulkanUnlitSpriteRenderer::EndFrame()
    {
        // The needed variables
        const VkDevice &device = m_renderer->GetDevice();
        const VkPhysicalDevice &physicalDevice = m_renderer->GetPhysicalDevice();
        const VkRenderPass &renderPass = m_renderer->GetRenderPass();
        const VkCommandBuffer &commandBuffer = m_renderer->GetCommandBuffer();

        std::stack<std::pair<VkBuffer, VkDeviceMemory>> tempVertexBufferDeviceMemoryStack;

        // go through each key
        for (auto keyValuePair : m_currentDrawPipelines)
        {
            // go through each pipeline
            u32 textureId = keyValuePair.first;
            std::stack<VulkanUnlitSpritePipeline *> &pipelineStack = keyValuePair.second;

            while (!pipelineStack.empty())
            {
                // get the pipeline, pop it from stack and push it to allocated stack
                VulkanUnlitSpritePipeline *spritePipeline = pipelineStack.top();
                pipelineStack.pop();
                m_allocatedPipelines[textureId].push(spritePipeline);

                const VkPipeline &pipeline = spritePipeline->GetPipeline();
                // auto projectionViewBindGroup = spritePipeline->GetProjectionViewBindGroup();
                // auto textureBindGroup = spritePipeline->GetTextureBindGroup();
                // auto brightnessThresholdBindGroup = spritePipeline->GetBrightnessThresholdBindGroup();

                // allocate or get vertex buffer.
                VkBuffer vertexBuffer;
                VkDeviceMemory vertexBufferMemory;
                if (m_vertexBufferDeviceMemoryStack.empty())
                {
                    size_t byteSize = SPRITE_RENDERER_MAX_SPRITES_PER_DRAW * FLOATS_PER_INSTANCE * sizeof(float);

                    vertexBuffer = VulkanUtil::Buffer.CreateVertexBuffer(physicalDevice,
                                                                         device,
                                                                         byteSize,
                                                                         &vertexBufferMemory);
                }
                else
                {
                    std::pair<VkBuffer, VkDeviceMemory> &vertexBufferDeviceMemory = m_vertexBufferDeviceMemoryStack.top();
                    vertexBuffer = vertexBufferDeviceMemory.first;
                    vertexBufferMemory = vertexBufferDeviceMemory.second;
                    m_vertexBufferDeviceMemoryStack.pop();
                }

                // push to temp stack
                tempVertexBufferDeviceMemoryStack.push({vertexBuffer, vertexBufferMemory});

                size_t byteSize = spritePipeline->InstanceIndex * FLOATS_PER_INSTANCE * sizeof(f32);
                VulkanUtil::DeviceMemory.Map(m_device, vertexBufferMemory, spritePipeline->DataArray, byteSize);

                // set pipeline
                vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, spritePipeline->GetPipeline());

                // UNIFORM DESCRIPTOR SET
                std::vector<VkDescriptorSet> descriptorSets = spritePipeline->GetDescriptorSets();
                // TODO: check if 1 is correct
                vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, spritePipeline->GetPipelineLayout(), 0, 1, &descriptorSets[0], 0, nullptr);

                // set vertex index buffer
                VkDeviceSize offsets[] = { 0 };
                vkCmdBindVertexBuffers(commandBuffer, 0, 1, &vertexBuffer, offsets);
                vkCmdBindIndexBuffer(commandBuffer, m_indexBuffer, 0, VK_INDEX_TYPE_UINT16);

                // draw
                vkCmdDrawIndexed(commandBuffer, 6 * spritePipeline->InstanceIndex, 1, 0, 0, 0);

                spritePipeline->InstanceIndex = 0;
            }
        }

        // return vertex buffers to stack
        while (!tempVertexBufferDeviceMemoryStack.empty())
        {
            m_vertexBufferDeviceMemoryStack.push(tempVertexBufferDeviceMemoryStack.top());
            tempVertexBufferDeviceMemoryStack.pop();
        }
    }
}

#endif