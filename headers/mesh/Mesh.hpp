
#ifndef BNS_MESH_HPP

#define BNS_MESH_HPP

#include <vector>
#include "camera/Camera.hpp"
#include "Mat4x4.hpp"

namespace bns
{
    enum class PrimitiveMode
    {
        POINTS,
        LINES,
        LINE_LOOP,
        LINE_STRIP,
        TRIANGLES,
        TRIANGLE_STRIP,
        TRIANGLE_FAN
    };

    class Framework;
    class Material;

    class Mesh
    {
    protected:
        const Framework &m_framework;

    public:
        Mesh(const Framework &framework);
        ~Mesh();

        /**
         * @brief The transform matrix of the mesh.
         */
        Mat4x4f Transform;

        /**
         * @brief The materials of the mesh.
         */
        std::vector<Material*> Materials;

        /**
         * @brief The number of indices of the mesh, to be used in the draw call.
        */
        size_t IndicesCount;

        /**
         * @brief Initialize the mesh
         */
        virtual void Initialize() = 0;

        /**
         * @brief Add a material to the mesh.
        */
        void AddMaterial(Material *material);

        /**
         * @brief Draw the mesh. Mesh must have materials assigned in order to be drawn.
         */
        void Draw(const Camera &camera);

        /**
         *  @brief Delete the mesh
         */
        virtual void Delete();
    };
}

#endif // !BNS_MESH_HPP
