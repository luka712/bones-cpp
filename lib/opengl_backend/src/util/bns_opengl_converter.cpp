#if USE_OPENGL

#include "util/bns_opengl_converter.hpp"
#include "bns_types.hpp"
#include <stdexcept>
#include <string>

namespace bns
{

    /// @brief Converts the vertex format to OpenGL vertex format.
    /// @param format The vertex format.
    /// @return The OpenGL vertex format which is number of components.
    size_t OpenGLConverter::Convert(VertexFormat format)
    {
        switch (format)
        {
        case VertexFormat::Float32x1:
            return 1;
        case VertexFormat::Float32x2:
            return 2;
        case VertexFormat::Float32x3:
            return 3;
        case VertexFormat::Float32x4:
            return 4;
        default:
            std::string msg = "OpenGLConverter::Convert: Invalid vertex format " + std::to_string((int)format) + ".";
            LOG(msg);
            BREAKPOINT();
            throw std::runtime_error(msg);
        }
    }

    /// @brief Converts the texture format to OpenGL texture format.
    /// @param format The texture format.
    /// @return The OpenGL texture format.
    GLenum OpenGLConverter::Convert(TextureFormat format)
    {
        switch (format)
        {
        case TextureFormat::BGRA_8_Unorm:
            return GL_BGRA;
        case TextureFormat::RGBA_8_Unorm:
            return GL_RGBA;
        default:
            std::string msg = "OpenGLConverter::Convert: Invalid texture format " + std::to_string((int)format) + ".";
            LOG(msg);
            BREAKPOINT();
            throw std::runtime_error(msg);
        }
    }

    /// @brief Converts the sampler min filter to OpenGL sampler min filter.
    /// @param filter The sampler min filter.
    /// @return The OpenGL sampler min filter.
    GLenum OpenGLConverter::Convert(SamplerMinFilter filter)
    {
        switch (filter)
        {
        case SamplerMinFilter::NEAREST:
            return GL_NEAREST;
        case SamplerMinFilter::LINEAR:
            return GL_LINEAR;
        case SamplerMinFilter::NEAREST_MIPMAP_NEAREST:
            return GL_NEAREST_MIPMAP_NEAREST;
        case SamplerMinFilter::LINEAR_MIPMAP_NEAREST:
            return GL_LINEAR_MIPMAP_NEAREST;
        case SamplerMinFilter::NEAREST_MIPMAP_LINEAR:
            return GL_NEAREST_MIPMAP_LINEAR;
        case SamplerMinFilter::LINEAR_MIPMAP_LINEAR:
            return GL_LINEAR_MIPMAP_LINEAR;
        default:
            std::string msg = "OpenGLConverter::Convert: Invalid sampler min filter " + std::to_string((int)filter) + ".";
            LOG(msg);
            BREAKPOINT();
            throw std::runtime_error(msg);
        }
    }

    /// @brief Converts the sampler mag filter to OpenGL sampler mag filter.
    /// @param filter The sampler mag filter.
    /// @return The OpenGL sampler mag filter.
    GLenum OpenGLConverter::Convert(SamplerMagFilter filter)
    {
        switch (filter)
        {
        case SamplerMagFilter::NEAREST:
            return GL_NEAREST;
        case SamplerMagFilter::LINEAR:
            return GL_LINEAR;
        default:
            std::string msg = "OpenGLConverter::Convert: Invalid sampler mag filter " + std::to_string((int)filter) + ".";
            LOG(msg);
            BREAKPOINT();
            throw std::runtime_error(msg);
        }
    }

}

#endif