#ifndef BNS_WGPU_BIND_GROUP_LAYOUT_ENTRY_UTIL_HPP

#define BNS_WGPU_BIND_GROUP_LAYOUT_ENTRY_UTIL_HPP

#include <webgpu/webgpu.h>
#include "data/Types.hpp"

namespace bns
{
    struct WebGPUBindGroupLayoutEntryUtil final
    {
        /**
         * @brief Create a bind group layout entry
         * @param binding The binding index.
         * @param shaderStage The shader stage. One of the WGPUShaderStageFlags.
         * Values: WGPUShaderStage_Vertex, WGPUShaderStage_Fragment, WGPUShaderStage_Compute
         * @return The bind group layout entry
         * @note By default the sampler, buffer, texture and storage texture are not used.
         */
        static WGPUBindGroupLayoutEntry CreateBindGroupLayoutEntry(u32 binding, WGPUShaderStageFlags shaderStage);

        /**
         * @brief Create a bind group layout entry for a sampler.
         * @param binding The binding index.
         * @param shaderStage The shader stage. One of the WGPUShaderStageFlags.
         * Values: WGPUShaderStage_Vertex, WGPUShaderStage_Fragment, WGPUShaderStage_Compute
         * @param samplerBindingLayout The sampler binding layout
         * @return The bind group layout entry
         * @note By default the buffer, texture and storage texture are not used.
         * @note The sampler is used.
         */
        static WGPUBindGroupLayoutEntry CreateBindGroupLayoutEntry(u32 binding,
                                                                   WGPUShaderStageFlags shaderStage,
                                                                   WGPUSamplerBindingLayout samplerBindingLayout);

        /**
         * @brief Create a bind group layout entry for a texture.
         * @param binding The binding index.
         * @param shaderStage The shader stage. One of the WGPUShaderStageFlags.
         * Values: WGPUShaderStage_Vertex, WGPUShaderStage_Fragment, WGPUShaderStage_Compute
         * @param textureBindingLayout The texture binding layout
         * @return The bind group layout entry
         * @note By default the sampler, buffer and storage texture are not used.
         * @note The texture is used.
        */
        static WGPUBindGroupLayoutEntry CreateBindGroupLayoutEntry(u32 binding,
                                                                   WGPUShaderStageFlags shaderStage,
                                                                   WGPUTextureBindingLayout textureBindingLayout);


        /**
         * @brief Create a bind group layout entry for a buffer.
         * @param binding The binding index.
         * @param shaderStage The shader stage. One of the WGPUShaderStageFlags.
         * Values: WGPUShaderStage_Vertex, WGPUShaderStage_Fragment, WGPUShaderStage_Compute
         * @param bufferBindingLayout The buffer binding layout
         * @return The bind group layout entry
         * @note By default the sampler, texture and storage texture are not used.
         * @note The buffer is used.
        */
        static WGPUBindGroupLayoutEntry CreateBindGroupLayoutEntry(u32 binding,
                                                                   WGPUShaderStageFlags shaderStage,
                                                                   WGPUBufferBindingLayout bufferBindingLayout);

        /**
         * @brief Create a bind group layout entry for a uniform buffer.
         * @param binding The binding index.
         * @param shaderStage The shader stage. One of the WGPUShaderStageFlags.
         * Values: WGPUShaderStage_Vertex, WGPUShaderStage_Fragment, WGPUShaderStage_Compute
         * @return The bind group layout entry
         * @note By default the sampler, texture and storage texture are not used.
         * @note The buffer is used.
         * @note The buffer is a uniform buffer.
        */
        static WGPUBindGroupLayoutEntry CreateUniformBufferLayoutEntry(u32 binding,
                                                                   WGPUShaderStageFlags shaderStage);

        /**
         * @brief Create a sampler layout entry.
         * @param binding The binding index.
         * @param shaderStage The shader stage. One of the WGPUShaderStageFlags.
         * Values: WGPUShaderStage_Vertex, WGPUShaderStage_Fragment, WGPUShaderStage_Compute
         * @return The bind group layout entry
         * @note By default the texture and storage texture are not used.
         * @note The sampler is used.
         * @note The buffer is a uniform buffer.
         * @note The sampler is a filtering sampler.
        */
        static WGPUBindGroupLayoutEntry CreateSamplerLayoutEntry(u32 binding, WGPUShaderStageFlags shaderStage);


        /**
         * @brief Create a texture layout entry.
         * @param binding The binding index.
         * @param shaderStage The shader stage. One of the WGPUShaderStageFlags.
         * Values: WGPUShaderStage_Vertex, WGPUShaderStage_Fragment, WGPUShaderStage_Compute
         * @return The bind group layout entry
         * @note By default the sampler and storage are not used.
         * @note The texture is used.
         * @note The buffer is a uniform buffer.
         * @note The texture is a float texture.
         * @note The texture is a 2D texture.
        */
        static WGPUBindGroupLayoutEntry CreateTextureLayoutEntry(u32 binding, WGPUShaderStageFlags shaderStage);
    };
}

#endif