#ifndef BNS_IMAGE_DATA_HPP

#define BNS_IMAGE_DATA_HPP

#include "Types.hpp"

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
    };
}

#endif // !BNS_IMAGE_DATA_HPP