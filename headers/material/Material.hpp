#pragma once

#ifndef BNS_MATERIAL_HPP

#define BNS_MATERIAL_HPP

#include <string>
#include "Color.hpp"
#include "camera/Camera.hpp"
#include "mesh/Mesh.hpp"

namespace bns
{
    class Material
    {
    public:
        /**
         * @brief The name of the material
         */
        std::string name;

        /**
         * @brief The diffuse color of the material
         */
        Color DiffuseColor;

        /**
         * @brief Initialize the material
         */
        virtual void Initialize() = 0;

        /**
         * @brief Render the passed in mesh.
         * @param camera The camera to render the mesh with.
         * @param mesh The mesh to render.
         * @return void
         */
        virtual void Draw(const Camera &camera, Mesh *inMesh) = 0;

        /**
         * @brief Render the passed in mesh multiple times.
         * If transform is empty, then the mesh will be ignored.
         * @param camera The camera to render the mesh with.
         * @param mesh The mesh to render.
         * @param transforms The transforms to render the mesh with.
         * @return void
         */
        virtual void Draw(const Camera &camera, const Mesh &mesh, std::vector<Mat4x4f> transforms) = 0;

        /**
         * @brief Render the passed in mesh multiple times.
         * Use flat transforms array where array is already prefilled with transforms matrices. Avoids copying of transforms to buffer.
         * @param camera The camera to render the mesh with.
         * @param mesh The mesh to render.
         * @param flatTransformsArray The flat array of transforms to render the mesh with. Array must be of length 16 * nOfInstances.
         * @param nOfInstances The number of instances to render.
         * @return void
         */
        virtual void DrawInstancedPrefilled(const Camera &camera, const Mesh &mesh, f32 *flatTransformsArray, i32 nOfInstances) = 0;

        /**
         * @brief Create a new copy of material
         */
        virtual Material *Copy() = 0;
    };
}

#endif