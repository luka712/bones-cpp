#ifndef BNS_ENGINE_H

#define BNS_ENGINE_H

#include "BnsMetal.hpp"

#include "Window.hpp"
#include "FileLoader.hpp"
#include "ImageLoader.hpp"
#include "loaders/BitmapSpriteFontLoader.hpp"
#include "material/MaterialFactory.hpp"
#include "geometry/GeometryBuilder.hpp"
#include "mesh/MeshFactory.hpp"
#include "sprite/SpriteRenderer.hpp"
#include "texture/TextureManager.hpp"
#include <webgpu/webgpu.h>
#include "Vec2.hpp"
#include "renderer/Renderer.hpp"
#include "effects/EffectFactory.hpp"
#include <functional>

namespace bns
{
    /// @brief The framework context.
    class Framework
    {
    private:
        WindowManager *m_windowManager;
        Renderer *m_renderer;
        GeometryBuilder *m_geometryBuilder;
        MeshFactory *m_meshFactory;
        MaterialFactory *m_materialFactory;
        ImageLoader *m_imageLoader;
        SpriteRenderer *m_spriteRenderer;
        BitmapSpriteFontLoader *m_bitmapSpriteFontLoader;
        TextureManager *m_textureFactory;
        EffectFactory *m_effectFactory;

        /// @brief Initialize the framework with WebGPU as the backend.
        void InitializeForWGPU(bns::WindowParameters windowParameters);

#ifdef __APPLE__
        /// @brief Initialize the framework with Metal as the backend.
        void InitializeForMetal(bns::WindowParameters windowParameters);
#endif

#ifdef WIN32
        /// @brief Initialize the framework with D3D11 as the backend.
        void InitializeForD3D11(bns::WindowParameters windowParameters);
#endif

#if USE_OPENGL
        /// @brief Initialize the framework with OpenGL as the backend.
        void InitializeForOpenGL(WindowParameters windowParameters);
#endif

#if USE_OPENGLES
        /// @brief Initialize the framework with OpenGL ES as the backend.
        void InitializeForOpenGLES(WindowParameters windowParameters);
#endif

    public:
        /// @brief Gets the window manager.
        /// @return The window manager.
        inline WindowManager &GetWindowManager() const
        {
            return *m_windowManager;
        }

        /**
         * @brief Get the renderer.
         */
        inline Renderer *GetRenderer() const
        {
            return m_renderer;
        }

        /**
         * @brief Get the geometry builder.
         */
        inline GeometryBuilder &GetGeometryBuilder() const
        {
            return *m_geometryBuilder;
        }

        /**
         * @brief Get the mesh factory.
         */
        inline MeshFactory &GetMeshFactory() const
        {
            return *m_meshFactory;
        }

        /**
         * @brief Get the material factory.
         */
        inline MaterialFactory &GetMaterialFactory() const
        {
            return *m_materialFactory;
        }

        /**
         * @brief Get the image loader.
         */
        inline ImageLoader &GetImageLoader() const
        {
            return *m_imageLoader;
        }

        /// @brief Gets the sprite renderer.
        /// @return The sprite renderer.
        inline SpriteRenderer *GetSpriteRenderer() const
        {
            return m_spriteRenderer;
        }

        /**
         * @brief Get the bitmap sprite font loader.
         */
        inline BitmapSpriteFontLoader &GetBitmapSpriteFontLoader() const
        {
            return *m_bitmapSpriteFontLoader;
        }

        /**
         * @brief Get the texture factory.
         */
        inline TextureManager &GetTextureManager() const
        {
            return *m_textureFactory;
        }

        /**
         * @brief Get the post process effect factory.
         */
        inline EffectFactory &GetEffectFactory() const
        {
            return *m_effectFactory;
        }

        /// @brief Gets the file loader.
        /// @return The file loader.
        inline FileLoader &GetFileLoader()
        {
            return FileLoader;
        }

        FileLoader FileLoader;

        Framework();
        ~Framework();

        /// @brief Initialize the framework.
        /// @param windowParameters The window parameters.
        /// @param callback The callback to be called after initialization.
        void Initialize(bns::WindowParameters windowParameters, std::function<void()> callback);

        /// @brief Draw callback for the framework.
        /// @param updateCallback The callback to be called on each frame when scene is ready to be drawn.
        void Draw(std::function<void()> updateCallback);
    };
}
#endif
