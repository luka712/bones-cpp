
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
}

#endif