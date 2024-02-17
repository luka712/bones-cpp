#if USE_WEBGPU

#ifndef BNS_WEBGPU_BIND_GROUP_LAYOUT_UTIL

#define BNS_WEBGPU_BIND_GROUP_LAYOUT_UTIL

#include "bns_types.hpp"
#include "bns_rendering_backend_types.hpp"
#include "map"
#include "bns_webgpu.hpp"
#include <vector>
#include <string>

namespace bns
{
    /// @brief Mapping class.
    struct WebGPUBindGroupLayoutEntry
    {
        /// @brief The constructor.
        WebGPUBindGroupLayoutEntry();

        /// @brief The destructor.
        ~WebGPUBindGroupLayoutEntry();

        u32 Binding;
        ShaderType Visibility;
        WGPUBufferBindingLayout BufferBindingLayout;
        WGPUSamplerBindingLayout SamplerBindingLayout;
        WGPUTextureBindingLayout TextureBindingLayout;
        WGPUStorageTextureBindingLayout StorageTextureBindingLayout;

        /// @brief Creates a new uniform buffer layout entry.
        /// @param binding The binding location.
        /// @param visibility The shader stage visibility.
        /// @return @ref WebGPUBindGroupLayoutEntry
        static WebGPUBindGroupLayoutEntry CreateUniformBufferLayoutEntry(u32 binding, ShaderType visibility);

        /// @brief Creates a new texture layout entry.
        /// @param binding The binding location.
        /// @param visibility The shader stage visibility.
        /// @return @ref WebGPUBindGroupLayoutEntry
        static WebGPUBindGroupLayoutEntry CreateTextureLayoutEntry(u32 binding, ShaderType visibility);

        /// @brief Creates a new sampler layout entry.
        /// @param binding The binding location.
        /// @param visibility The shader stage visibility.
        /// @return @ref WebGPUBindGroupLayoutEntry
        static WebGPUBindGroupLayoutEntry CreateSamplerLayoutEntry(u32 binding, ShaderType visibility);
    };

    struct WebGPUBindGroupLayoutUtil
    {
    private:
        /// @brief Maps the shader stage to WGPUShaderStage_{stage}
        /// @param type The type of shader.
        /// @return The shader stage.
        static u32 MapShaderStage(ShaderType type);

    public:

        /// @brief Creates a new bind group layout.
        /// @param device The device.
        /// @param bindGroupEntries The list of @ref WebGPUBindGroupLayoutEntry. Our wrapper class for @ref WGPUBindGroupLayoutEntry.
        /// @param label The label. By default ""
        /// @return @ref WGPUBindGroupLayout.
        static WGPUBindGroupLayout Create(WGPUDevice device, std::vector<WebGPUBindGroupLayoutEntry>& bindGroupEntries, std::string label = "");

        /// @brief Release a layout.
        /// @param bindGroupLayout 
        static void Dispose(WGPUBindGroupLayout bindGroupLayout);
    };
}

#endif

#endif