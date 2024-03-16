#if USE_OPENGL

#include "pipelines/bns_opengl_unlit_render_pipeline.hpp"
#include "bns_opengl_util.hpp"
#include "loaders/bns_file_loader.hpp"
#include "texture/bns_opengl_texture2d.hpp"
#include "buffers/bns_opengl_vertex_buffer.hpp"
#include "buffers/bns_opengl_index_buffer.hpp"

namespace bns
{
    OpenGLUnlitRenderPipeline::OpenGLUnlitRenderPipeline(UniformBuffer<Mat4x4f> *cameraBuffer, InstanceBuffer<Mat4x4f> *modelBuffer)
        : m_cameraBuffer(static_cast<OpenGLUniformBuffer<Mat4x4f> *>(cameraBuffer)),
          m_modelBuffer(static_cast<OpenGLInstanceBuffer<Mat4x4f> *>(modelBuffer)),
          m_vao(0),
          m_lastVerticesBuffer(0)
    {
        m_textureTilling = Vec2f::One();
        m_diffuseColor = Color::White();
    }

    void OpenGLUnlitRenderPipeline::SetDiffuseColor(Color color)
    {
        m_diffuseColor = color;
        m_diffuseColorBuffer->Update(color);
    }

    void OpenGLUnlitRenderPipeline::SetTextureTilling(Vec2f tilling)
    {
        m_textureTilling = tilling;
        m_textureTillingBuffer->Update(tilling);
    }

    void OpenGLUnlitRenderPipeline::SetDiffuseTexture(Texture2D *texture)
    {
        m_diffuseTexture = texture;
    }

    void OpenGLUnlitRenderPipeline::CreateProgram()
    {
        u32 vertexShader = OpenGLUtil::Shader.CreateVertexShader("shaders/opengl/material/unlit_material_vs.glsl");
        u32 fragmentShader = OpenGLUtil::Shader.CreateFragmentShader("shaders/opengl/material/unlit_material_fs.glsl");

        // Create program.
        m_program = OpenGLUtil::Program.Create(vertexShader, fragmentShader);

        // Delete shaders.
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        LOG("WebGPUUnlitMaterialPipeline: Shader module created.");
    }

    void OpenGLUnlitRenderPipeline::CreateVAO(OpenGLVertexBuffer *vertexBuffer)
    {
        if (m_vao != 0)
        {
            glDeleteVertexArrays(1, &m_vao);
        }

        // Here we create VAO that uses both vertex and instance buffer.

        GLuint verticesBuffer = vertexBuffer->GetBuffer();
        GLuint transformBuffer = m_modelBuffer->GetBuffer();

        std::vector<OpenGLBufferLayoutDescriptor> bufferLayoutDescriptors(2);

        // Describe the vertex buffer layout
        bufferLayoutDescriptors[0].Buffer = verticesBuffer;
        bufferLayoutDescriptors[0].IsInstanced = false;
        bufferLayoutDescriptors[0].BufferLayoutDescriptor.Stride = (3 + 4 + 2) * sizeof(float);
        bufferLayoutDescriptors[0].BufferLayoutDescriptor.StepMode = VertexStepMode::Vertex;
        bufferLayoutDescriptors[0].BufferLayoutDescriptor.Attributes.push_back(BufferLayoutAttributeDescriptor(VertexFormat::Float32x3, 0, 0));
        bufferLayoutDescriptors[0].BufferLayoutDescriptor.Attributes.push_back(BufferLayoutAttributeDescriptor(VertexFormat::Float32x4, 1, 3 * sizeof(float)));
        bufferLayoutDescriptors[0].BufferLayoutDescriptor.Attributes.push_back(BufferLayoutAttributeDescriptor(VertexFormat::Float32x2, 2, (3 + 4) * sizeof(float)));

        // Describe the instance buffer layout
        bufferLayoutDescriptors[1].Buffer = transformBuffer;
        bufferLayoutDescriptors[1].IsInstanced = true;
        bufferLayoutDescriptors[1].BufferLayoutDescriptor.Stride = sizeof(float) * 16;
        bufferLayoutDescriptors[1].BufferLayoutDescriptor.StepMode = VertexStepMode::Instance;
        bufferLayoutDescriptors[1].BufferLayoutDescriptor.Attributes.push_back(BufferLayoutAttributeDescriptor(VertexFormat::Float32x4, 3, 0));
        bufferLayoutDescriptors[1].BufferLayoutDescriptor.Attributes.push_back(BufferLayoutAttributeDescriptor(VertexFormat::Float32x4, 4, 4 * sizeof(float)));
        bufferLayoutDescriptors[1].BufferLayoutDescriptor.Attributes.push_back(BufferLayoutAttributeDescriptor(VertexFormat::Float32x4, 5, 8 * sizeof(float)));
        bufferLayoutDescriptors[1].BufferLayoutDescriptor.Attributes.push_back(BufferLayoutAttributeDescriptor(VertexFormat::Float32x4, 6, 12 * sizeof(float)));

        m_vao = OpenGLUtil::VertexArrayObject.Create(bufferLayoutDescriptors, "Unlit Pipeline Vertex Array Object.");
    }

    void OpenGLUnlitRenderPipeline::CreateResources()
    {
        m_textureTillingBuffer = new OpenGLUniformBuffer<Vec2f>("Unlit Pipeline Texture Tilling Buffer");
        m_textureTillingBuffer->Initialize();
        m_textureTillingBuffer->Update(m_textureTilling);

        m_diffuseColorBuffer = new OpenGLUniformBuffer<Color>("Unlit Pipeline Diffuse Color Buffer");
        m_diffuseColorBuffer->Initialize();
        m_diffuseColorBuffer->Update(m_diffuseColor);

        m_defaultEmptyTexture = OpenGLTexture2D::CreateEmpty(1, 1);
        m_diffuseTexture = m_defaultEmptyTexture;
    }

    void OpenGLUnlitRenderPipeline::Initialize()
    {
        CreateProgram();
        CreateResources();
    }

    void OpenGLUnlitRenderPipeline::Render(VertexBuffer *vertexBuffer, IndexBuffer *indexBuffer, u32 instanceCount)
    {
        OpenGLVertexBuffer *openGLVertexBuffer = static_cast<OpenGLVertexBuffer *>(vertexBuffer);
        OpenGLIndexBuffer *openGLIndexBuffer = static_cast<OpenGLIndexBuffer *>(indexBuffer);
        OpenGLTexture2D *openGLDiffuseTexture = static_cast<OpenGLTexture2D *>(m_diffuseTexture);

        // If it was changed, we create a new VAO:
        if (m_lastVerticesBuffer != openGLVertexBuffer->GetBuffer())
        {
            // Crate VAO. Internally deleted old one.
            CreateVAO(openGLVertexBuffer);
            m_lastVerticesBuffer = openGLVertexBuffer->GetBuffer();
        }

        // Bind program.
        glUseProgram(m_program);

        // Bind the vao. It contains all the information about the vertex buffer layout ( vertices + instances)
        glBindVertexArray(m_vao);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, openGLIndexBuffer->GetBuffer());

        glBindBufferBase(GL_UNIFORM_BUFFER, 0, m_textureTillingBuffer->GetBuffer());
        glBindBufferBase(GL_UNIFORM_BUFFER, 1, m_cameraBuffer->GetBuffer());
        glBindBufferBase(GL_UNIFORM_BUFFER, 2, m_diffuseColorBuffer->GetBuffer());

        glActiveTexture(GL_TEXTURE0);

        glBindTexture(GL_TEXTURE_2D, openGLDiffuseTexture->GetTexture());

        glDrawElementsInstanced(GL_TRIANGLES, openGLIndexBuffer->GetIndicesCount(), GL_UNSIGNED_SHORT, 0, instanceCount);
    }
}
#endif