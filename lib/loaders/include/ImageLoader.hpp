#ifndef BNS_IMAGE_LOADER_HPP

#define BNS_IMAGE_LOADER_HPP

#include "bns_types.hpp"
#include "ImageData.hpp"
#include <string>

namespace bns
{
    /**
     * @brief Expand or change the loaded format.
     */
    enum PixelFormat
    {
        /**
         * @brief Don't do anything if none.
         */
        NONE,

        /**
         * @brief Expand smaller formats to RGBA. For example RGB can be expanded to RGBA.
         */
        RGBA
    };

    class ImageLoader
    {
    public:
        /**
         * @brief Load the image data from path.
         *
         * @param path - file path
         * @return the image data.
         * @note The image data is allocated on the heap. It is the responsibility of the user to delete it.
         */
        ImageData *LoadImage(std::string path);

        /**
         * @brief Load the image data from path.
         *
         * @param path - file path
         * @param expand_to_format - if actual returned format is less then 'exapand_to_format', format is expanded. For example RGB to RGBA.
         * @return ImageData*
         * @note The image data is allocated on the heap. It is the responsibility of the user to delete it.
         */
        ImageData *LoadImage(std::string path, PixelFormat expand_to_format);
    };
}

#endif // !BNS_IMAGE_LOADER_HPP