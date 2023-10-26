#ifndef BNS_WEBGPU_BIND_GROUP_DESCRIPTOR_UTIL_HPP

#define BNS_WEBGPU_BIND_GROUP_DESCRIPTOR_UTIL_HPP

#include <webgpu/webgpu.h>
#include "data/Types.hpp"
#include <string>

namespace bns
{
    struct WebGPUBindGroupDescriptorUtil final
    {
        /// @brief Creates a bind group descriptor.
        ///
        /// This function is used to create a bind group descriptor, which represents a collection
        /// of resource bindings based on a specified bind group layout.
        ///
        /// @param layout The bind group layout specifying the expected resource bindings.
        /// @param entry An array of bind group entries providing the actual resource bindings.
        /// @param entryCount The number of entries in the 'entry' array.
        /// @param label An optional label for the bind group descriptor, useful for debugging.
        ///
        /// @return WGPUBindGroupDescriptor The created bind group descriptor.
        ///
        /// @note The caller is responsible for managing the memory associated with the bind group descriptor.
        /// It's recommended to use this function within a scope where the descriptor's lifetime is well-defined.
        ///
        /// Example usage:
        /// ```
        /// WGPUBindGroupLayout bindGroupLayout = ...; // Obtain or create the bind group layout.
        /// WGPUBindGroupEntry entries[] = { ... };     // Specify the resource bindings.
        /// u32 entryCount = sizeof(entries) / sizeof(entries[0]);
        /// WGPUBindGroupDescriptor bindGroupDescriptor = WGPUBindGroupDescriptor::Create(bindGroupLayout, entries, entryCount, "MyBindGroup");
        /// // Use the bind group descriptor in further API calls.
        /// ```
        static WGPUBindGroupDescriptor Create(WGPUBindGroupLayout layout, WGPUBindGroupEntry *entry, u32 entryCount, std::string& label);

                /// @brief Creates a bind group descriptor.
        ///
        /// This function is used to create a bind group descriptor, which represents a collection
        /// of resource bindings based on a specified bind group layout.
        ///
        /// @param layout The bind group layout specifying the expected resource bindings.
        /// @param entry An array of bind group entries providing the actual resource bindings.
        /// @param entryCount The number of entries in the 'entry' array.
        ///
        /// @return WGPUBindGroupDescriptor The created bind group descriptor.
        ///
        /// @note The caller is responsible for managing the memory associated with the bind group descriptor.
        /// It's recommended to use this function within a scope where the descriptor's lifetime is well-defined.
        ///
        /// Example usage:
        /// ```
        /// WGPUBindGroupLayout bindGroupLayout = ...; // Obtain or create the bind group layout.
        /// WGPUBindGroupEntry entries[] = { ... };     // Specify the resource bindings.
        /// u32 entryCount = sizeof(entries) / sizeof(entries[0]);
        /// WGPUBindGroupDescriptor bindGroupDescriptor = WGPUBindGroupDescriptor::Create(bindGroupLayout, entries, entryCount, "MyBindGroup");
        /// // Use the bind group descriptor in further API calls.
        /// ```
        static WGPUBindGroupDescriptor Create(WGPUBindGroupLayout layout, WGPUBindGroupEntry *entry, u32 entryCount);
    };
}

#endif