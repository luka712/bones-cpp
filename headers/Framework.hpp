#ifndef BNS_ENGINE_H

#define BNS_ENGINE_H

#include "window/Window.hpp"
#include "loaders/FileLoader.hpp"
#include "loaders/ImageLoader.hpp"
#include "material/MaterialFactory.hpp"
#include "geometry/GeometryBuilder.hpp"
#include "mesh/MeshFactory.hpp"
#include <webgpu/webgpu.h>
#include <Metal/Metal.hpp>

namespace bns
{
    struct FrameworkContext
    {
        /**
         * @brief The webgpu device.
         * This is global interface of the device.
         */
        WGPUDevice WebGPUDevice;

        /**
         * @brief The current render pass encoder.
        */
        WGPURenderPassEncoder CurrentWebGPURenderPassEncoder;

        /**
         * @brief The metal device.
        */
        MTL::Device *MetalDevice;

        /**
         * @brief The current render command encoder.
        */
        MTL::RenderCommandEncoder *CurrentMetalRenderCommandEncoder;
    };


    /**
     * @brief The Framework class
     */
    class Framework
    {
    private:
        WindowManager *m_windowManager;
        GeometryBuilder *m_geometryBuilder;
        MeshFactory *m_meshFactory;
        MaterialFactory *m_materialFactory;
        ImageLoader *m_imageLoader;
        Directory *m_directory;

        void InitializeForMetal(bns::WindowParameters windowParameters);
        void InitializeForWGPU(bns::WindowParameters windowParameters);

    public:
        FrameworkContext Context;

        /**
         * @brief Get the window manager.
         */
        inline WindowManager &GetWindowManager() const
        {
            return *m_windowManager;
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

        /**
         * @brief Get the directory.
         */
        inline Directory &GetDirectory() const
        {
            return *m_directory;
        }
        

        FileLoader FileLoader;

        Framework();
        ~Framework();

        void Initialize(bns::WindowParameters windowParameters);
    };
}
#endif
