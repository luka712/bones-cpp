#include "ImageLoader.hpp"

#include <stb/stb_image.hpp>


bns::ImageData *bns::ImageLoader::LoadImage(std::string path)
{
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

