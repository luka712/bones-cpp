#ifndef METAL_BASIC_MESH_TEXTURED_TEST_MATERIAL_HPP

#define METAL_BASIC_MESH_TEXTURED_TEST_MATERIAL_HPP

#include "material/Material.hpp"
#include "textures/Texture2D.hpp"
#include <Metal/Metal.hpp>

namespace bns
{
    class Framework;

    /**
     * Material where mesh is embedded in shader.
     * This is test material to see if shader can be compiled and set up.
     * This is not a real material.
     * This is not a material that should be used in production.
     */
    class MetalBasicMeshTexturedTestMaterial final : public Material
    {
    private:
        Framework &m_framework;

        /**
         * @brief The pipeline for the material.
         * This is used to draw the material.
         */
        MTL::RenderPipelineState *m_pipeline;

        /**
         * @brief The texture for the material.
         */
        Texture2D *m_texture;

    public:
        MetalBasicMeshTexturedTestMaterial(Framework &framework, Texture2D* texture);
        ~MetalBasicMeshTexturedTestMaterial();

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

#endif // !METAL_BASIC_MESH_TEST_MATERIAL_HPP