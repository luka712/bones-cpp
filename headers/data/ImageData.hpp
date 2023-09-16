#ifndef BNS_IMAGE_DATA_HPP

#define BNS_IMAGE_DATA_HPP

#include "data/Types.hpp"

namespace bns 
{
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
}

#endif // !BNS_IMAGE_DATA_HPP