#include "loaders/ImageLoader.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.hpp>


#pragma region ImageData 

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
    Destroy();
}

void bns::ImageData::Destroy()
{
    if (Data != nullptr)
    {
        free(Data);
    }
    Data = nullptr;
    Width = 0;
    Height = 0;
    Channels = 0;
}

#pragma endregion


#pragma region ImageLoader

bns::ImageLoader::ImageLoader(Directory& directory)
: m_directory(directory)
{}

bns::ImageData *bns::ImageLoader::LoadImage(std::string path)
{
    // TODO: get rid of root
    std::string root = m_directory.Root();

    // Load image at specified path
    int width, height, nr_channels;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nr_channels, STBI_rgb_alpha);

    // If there's an error, display it.
    if (data == nullptr)
    {

        throw std::invalid_argument("ImageLoader::LoadImage: Could not find texture under path: " + path);
    }

    return new ImageData(data, width, height, 4);
}

bns::ImageData *bns::ImageLoader::LoadImage(std::string path, bns::PixelFormat format)
{
    return LoadImage(path);
}



#pragma endregion