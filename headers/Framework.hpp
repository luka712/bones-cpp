#ifndef BNS_ENGINE_H

#define BNS_ENGINE_H

#include "BnsMetal.hpp"

#include "Window.hpp"
#include "loaders/bns_file_loader.hpp"
#include "ImageLoader.hpp"
#include "loaders/BitmapSpriteFontLoader.hpp"
#include "material/MaterialFactory.hpp"
#include "geometry/GeometryBuilder.hpp"
#include "mesh/MeshFactory.hpp"
#include "sprite/bns_sprite_renderer.hpp"
#include "texture/TextureManager.hpp"
#include <webgpu/webgpu.h>
#include "Vec2.hpp"
#include "renderer/bns_renderer.hpp"
#include "effects/EffectFactory.hpp"
#include <functional>
#include "time/TimeManager.hpp"

namespace bns
{
    struct FrameworkDescription
    {
        FrameworkDescription();

        /// @brief The renderer type.
        RendererType RendererType;

    };

    /// @brief The framework context.
    class Framework
    {
    private:
        LifecycleState m_lifecycleState;
        RendererType m_currentRendererType;

        // Cache the window parameters and initialize callback so we can reinitialize the framework.
        WindowParameters m_windowParameters;
        std::function<void()> m_initializeCallback;

        Events *m_events;
        WindowManager *m_windowManager;
        TimeManager *m_timeManager;
        Renderer *m_renderer;
        GeometryBuilder *m_geometryBuilder;
        MeshFactory *m_meshFactory;
        MaterialFactory *m_materialFactory;
        ImageLoader *m_imageLoader;
        SpriteRenderer *m_spriteRenderer;
        BitmapSpriteFontLoader *m_bitmapSpriteFontLoader;
        TextureManager *m_textureFactory;
        EffectFactory *m_effectFactory;

        /// @brief Setup the framework render objects. OpenGL, WebGPU, Metal etc...
        void CreateRenderObjects();

        /// @brief Destroys the framework render objects. OpenGL, WebGPU, Metal etc...
        void DestroyRenderObjects();

        /// @brief Initialize the framework with WebGPU as the backend.
        void InitializeForWGPU(bns::WindowParameters windowParameters);

#if USE_METAL
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

#if USE_VULKAN
        /// @brief Initialize the framework with Vulkan as the backend.
        void InitializeForVulkan(WindowParameters windowParameters);
#endif
        void OnDraw();

    public:
        /// @brief The update callback.
        std::function<void(Time time)> UpdateCallback;
        /// @brief The draw callback.
        std::function<void()> DrawCallback;

        /// @brief Gets the events.
        /// @return The events.
        inline Events &GetEvents() const
        {
            return *m_events;
        }

        /// @brief Gets the type of the current renderer.
        /// @return The type of the current renderer.
        inline RendererType GetCurrentRenderer() const
        {
            return m_currentRendererType;
        }

        /// @brief Gets the window manager.
        /// @return The window manager.
        inline WindowManager &GetWindowManager() const
        {
            return *m_windowManager;
        }

        /// @brief Get the renderer.
        inline Renderer *GetRenderer() const { return m_renderer; }

        /// @brief Get the time manager.
        inline TimeManager *GetTimeManager() const { return m_timeManager; }

        /// @brief Get the geometry builder.
        inline GeometryBuilder &GetGeometryBuilder() const { return *m_geometryBuilder; }

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

        /// @brief Get the texture factory.
        inline TextureManager &GetTextureManager() const { return *m_textureFactory; }

        /// @brief Get the post process effect factory.
        inline EffectFactory &GetEffectFactory() const { return *m_effectFactory; }

        /// @brief Gets the file loader.
        /// @return The file loader.
        inline FileLoader &GetFileLoader() { return FileLoader; }

        FileLoader FileLoader;

        /// @brief The constructor
        /// @param desc The parameters.
        Framework(FrameworkDescription desc = FrameworkDescription());

        /// @brief The destructor.
        ~Framework();

        /// @brief Initialize the framework.
        /// @param windowParameters The window parameters.
        /// @param callback The callback to be called after initialization.
        void Initialize(bns::WindowParameters windowParameters, std::function<void()> callback);

        /// @brief Switches the renderer.
        /// @param rendererType The renderer type.
        void SwitchRenderer(RendererType rendererType);

        /// @brief Destroys the framework.
        void Destroy();
    };
}
#endif
