#if USE_VULKAN

#ifndef VULKAN_INSTANCE_UTIL_HPP

#define VULKAN_INSTANCE_UTIL_HPP

#include "BnsVulkan.hpp"
#include <vector>
#include <string>

namespace bns
{
    /// @brief Utility class for @ref VkInstance struct
    struct VulkanInstanceUtil
    {
        /// @brief Creates @ref VkInstance struct with default values
        /// @param appInfo The @ref VkApplicationInfo struct
        /// @param enableExtensions The list of extensions to enable
        /// @param enableLayers The list of layers to enable
        /// @return The created @ref VkInstance struct
        static VkInstance Create(const VkApplicationInfo &appInfo,
                                 const std::vector<std::string> &enableExtensions,
                                 const std::vector<std::string> &enableLayers);


        /// @brief Checks if the given extension is supported
        /// @param extensionName The name of the extension to check
        /// @return True if the extension is supported, false otherwise
        static bool IsExtensionSupported(const std::string& extensionName);

        /// @brief Checks if the given layer is supported
        /// @param layerName The name of the layer to check
        /// @return True if the layer is supported, false otherwise
        static bool IsLayerSupported(const std::string& layerName);

        /// @brief Prints the available extensions and layers
        static void PrintAvailableExtensionsAndLayers();
    };
}

#endif // !VULKAN_INSTANCE_UTIL_HPP

#endif