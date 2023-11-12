#ifndef BNS_TEXTURE_FACTORY_IMPL_HPP

#define BNS_TEXTURE_FACTORY_IMPL_HPP

#include "texture/Texture2D.hpp"
#include "texture/TextureManager.hpp"
#include "ImageLoader.hpp"
#include "renderer/Renderer.hpp"
#include <map>

namespace bns
{

    class TextureManagerImpl final : public TextureManager
    {
private:
        /// @brief The renderer.
        Renderer *m_renderer;

    protected:
        /// @brief The implementation of this should just create a texture instance according to the backend renderer being used.
        /// In short it should be WebGPU, Metal, OpenGL, Vulkan or DirectX Texture2D implementation
        /// @param imageData The image data.
        /// @param textureUsageFlags The texture usage flags.
        /// @param format The texture format.
        /// @return The texture instance.
        Texture2D *CreateBackendImplTexture(ImageData *imageData, i32 textureUsageFlags, TextureFormat format) override;

    public:
        TextureManagerImpl(Renderer* renderer,  ImageLoader* imageLoader);
    };
}

#endif // !BNS_TEXTURE_FACTORY_IMPL_HPP