#ifndef BNS_WEBGPU_BASIC_MATERIAL_HPP

#define BNS_WEBGPU_BASIC_MATERIAL_HPP

#include <webgpu/webgpu.h>
#include "material/basic/BasicMaterial.hpp"
#include "renderer/WebGPURenderer.hpp"
#include "FileLoader.hpp"

namespace bns
{
    class Framework;

    class WebGPUBasicMaterial final : public BasicMaterial
    {
    private:
        /// @brief The renderer.
        WebGPURenderer* m_renderer;

        /// @brief The file loader.
        FileLoader* m_fileLoader;

        /**
         * Max instances that can be created for this material if instanced drawing is used.
         */
        i32 m_maxInstances;

        /**
         * @brief The pipeline for the material.
         * This is used to draw the material.
         */
        WGPURenderPipeline m_pipeline;

        /**
         * @brief The bind group layout for the material.
         * This is used to bind the uniform buffer to the shader.
         */
        WGPUBindGroup m_uniformsBindGroup;

        /**
         * @brief The uniform buffer for the material.
         * This is used to pass data to the shader.
         * For global (projectionViewMatrix)
         */
        WGPUBuffer m_uniformGlobalBuffer;

        /**
         * @brief The uniform buffer for the material.
         * This is used to pass data to the shader.
         * For local (modelMatrix or transformMatrix, diffuseColor)
         */
        WGPUBuffer m_uniformInstancesBuffer;

        /**
         * @brief The result of InitializeStates call.
         * Contains the vertex and fragment states.
         */
        struct InitializeStatesResult
        {
            WGPUVertexState VertexState;
            WGPUFragmentState FragmentState;
        };

        InitializeStatesResult InitializeStates();

        /**
         * @brief The result of InitializeBuffers call.
         */
        struct InitializeBuffersResult
        {
            WGPUBindGroupLayout UniformsBindGroupLayout;
        };

        InitializeBuffersResult InitializeBuffers();

    public:
        WebGPUBasicMaterial(Framework &framework);
        /**
         * @brief Construct a new Basic Material object
         * @param framework The framework reference.
         * @param maxInstances The max instances to draw.
         */
        WebGPUBasicMaterial(Framework &framework, i32 maxInstances);

        /**
         * @brief Initialize the material.
         */
        void Initialize() override;

        /**
         * @brief Render the passed in mesh.
         * @param camera The camera to render the mesh with.
         * @param mesh The mesh to render.
         * @return void
         */
        void Draw(const Camera &camera, Mesh *mesh) override;

        /**
         * @brief Render the passed in mesh multiple times.
         * If transform is empty, then the mesh will be ignored.
         * @param camera The camera to render the mesh with.
         * @param mesh The mesh to render.
         * @param transforms The transforms to render the mesh with.
         * @return void
         */
        void Draw(const Camera &camera, const Mesh &mesh, std::vector<Mat4x4f> transforms) override;

        /**
         * @brief Render the passed in mesh multiple times.
         * Use flat transforms array where array is already prefilled with transforms matrices. Avoids copying of transforms to buffer.
         * @param camera The camera to render the mesh with.
         * @param mesh The mesh to render.
         * @param flatTransformsArray The flat array of transforms to render the mesh with. Array must be of length 16 * nOfInstances.
         * @param nOfInstances The number of instances to render.
         * @return void
         */
        void DrawInstancedPrefilled(const Camera &camera, const Mesh &mesh, f32 *flatTransformsArray, i32 nOfInstances) override;

        /**
         * @brief Create a new copy of material
         */
        Material *Copy() override;
    };
}

#endif