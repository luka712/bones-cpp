
#ifndef BNS_RENDERING_BACKEND_TYPES_HPP

#define BNS_RENDERING_BACKEND_TYPES_HPP

namespace bns
{
    /// @brief The shader type.
    enum class ShaderType
    {
        Vertex,
        Fragment,
        Compute,
        Geometry,
    };

     /// @brief The step mode of the buffer layout.
    enum class VertexStepMode
    {
        /// @brief Step of vertex shader per single vertex.
        Vertex,

        /// @brief Step of vertex shader per single instance.
        Instance,
    };

    /// @brief The vertex format.
    enum class VertexFormat
    {
        Float32x1,
        Float32x2,
        Float32x3,
        Float32x4,
    };

    /// @brief The cull mode.
    /// @note The cull mode is used to determine which face to cull.
    enum class CullMode
    {
        None,
        Front,
        Back,
        FrontAndBack
    };

    /// @brief The front face.
    /// @note The front face is used to determine which face is the front face.
    enum class FrontFace 
    {
        Clockwise,
        CounterClockwise
    };

    /// @brief The binding type.
    enum class BindingType 
    {
        /// @brief The binding type for uniform buffer.
        Uniform,

        /// @brief The binding type for texture and sampler.
        CombinedTextureSampler,
    };

    /// @brief The usage of the texture.
    /// For WebGPU usage see https://developer.mozilla.org/en-US/docs/Web/API/GPUTexture/usage
    enum TextureUsage
    {
        /// @brief When usage is not relevant. Such as when working with OpenGL textures.
        None = 0x0,

        /// @brief The texture can be used as the source of a copy operation. For example copy texture to buffer.
        CopySrc = 0x1,

        /// @brief The texture can be used as the destination of a copy operation. For example copy buffer to texture.
        CopyDst = 0x2,

        /// @brief The texture can be used as a sampled texture in a shader.
        /// For example as a resource when in bind group entry, which adheres to a entry specified with texture binding layout.
        TextureBinding = 0x4,

        /// @brief The texture can be used as a storage texture in a shader.
        /// For example as a resource when in bind group entry, which adheres to a entry specified with storage texture binding layout.
        TextureStorage = 0x8,

        /// @brief The texture can be used as a color or depth/stencil attachment in render pass.
        RenderAttachment = 0x10,

        /// @brief Can be used as copy destination and texture binding.
        CopyDst_TextureBinding = CopyDst | TextureBinding,
        /// @brief Can be used as copy destination, texture binding and render attachment.
        CopyDst_TextureBinding_RenderAttachment = CopyDst | TextureBinding | RenderAttachment,
        CopyDst_CopySrc_TextureBinding_RenderAttachment = CopyDst | CopySrc | TextureBinding | RenderAttachment,
    };

    /// @brief The format of the texture.
    enum class TextureFormat
    {
        /// @brief Ordinary format with four 8-bit normalized unsigned integer components in RGBA order.
        RGBA_8_Unorm = 0x1,

        /// @brief Ordinary format with four 8-bit normalized unsigned integer components in BGRA order.
        BGRA_8_Unorm = 0x2,
    };

    /// @brief The min filter.
    enum class SamplerMinFilter
    {
        NEAREST = 0x1,
        LINEAR = 0x2,
        NEAREST_MIPMAP_NEAREST = 0x3,
        LINEAR_MIPMAP_NEAREST = 0x4,
        NEAREST_MIPMAP_LINEAR = 0x5,
        LINEAR_MIPMAP_LINEAR = 0x6,
    };

    /// @brief The mag filter.
    enum class SamplerMagFilter
    {
        NEAREST = 0x1,
        LINEAR = 0x2,
    };

    
}

#endif