#include "ImageData.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.hpp>


bns::ImageData::ImageData(void *data, bns::i32 width, bns::i32 height, bns::i32 channels)
{
    Data = data;
    Width = width;
    Height = height;
    Channels = channels;
}

bns::ImageData::ImageData()
{
    Data = nullptr;
}

bns::ImageData::~ImageData()
{
    if (Data != nullptr)
    {
        stbi_image_free(Data);
    }
}
