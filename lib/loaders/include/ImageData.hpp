#ifndef BNS_IMAGE_DATA_HPP

#define BNS_IMAGE_DATA_HPP

#include "bns_types.hpp"

namespace bns
{
    /// @brief The data of an image
    struct ImageData final
    {
        /// @brief The data of the image
        void *Data;

        /// @brief The width of the image
        i32 Width;

        /// @brief The height of the image
        i32 Height;

        /// @brief The number of channels in the image
        i32 Channels;

        /// @brief Construct a new Image Data object
        ImageData();

        /// @brief Construct a new Image Data object
        /// @param data The data of the image
        /// @param width The width of the image
        /// @param height The height of the image
        /// @param channels The number of channels in the image
        ImageData(void *data, i32 width, i32 height, i32 channels);

        /// @brief Destroy the Image Data object
        ~ImageData();

        /// @brief Gets the size of the image data
        inline size_t GetSize() const { return Width * Height * Channels; }
    };
}

#endif // !BNS_IMAGE_DATA_HPP