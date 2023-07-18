#ifndef BNS_IMAGE_LOADER_HPP

#define BNS_IMAGE_LOADER_HPP

#include "data/Types.hpp"
#include "file/Directory.hpp"
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

    /**
     * @brief Interface for image data.
     */
    struct ImageData final
    {

    public:
        void *Data;
        i32 Width;
        i32 Height;
        i32 Channels;

        /**
         * @brief Construct a new Image Data object
         */
        ImageData();

        /**
         * @brief Construct a new SDLImageData object
         *
         * @param data
         * @param width
         * @param height
         * @param channels
         */
        ImageData(void *data, i32 width, i32 height, i32 channels);

        /**
         * @brief Destroy the Image Data object
         */
        virtual ~ImageData();

        /**
         * @brief Destroy the image data.
         */
        virtual void Destroy();
    };

    class ImageLoader
    {
    private:
        Directory &m_directory;

    public:
        /**
         * @brief Construct a new Image Loader object
         */
        ImageLoader(Directory &directory);

        /**
         * @brief Load the image data from path.
         *
         * @param path - file path
         * @return the image data.
         */
        ImageData *LoadImage(std::string path);

        /**
         * @brief Load the image data from path.
         *
         * @param path - file path
         * @param expand_to_format - if actual returned format is less then 'exapand_to_format', format is expanded. For example RGB to RGBA.
         * @return ImageData*
         */
        ImageData *LoadImage(std::string path, PixelFormat expand_to_format);
    };
}

#endif // !BNS_IMAGE_LOADER_HPP