#ifndef BNS_METAL_MESH_FACTORY_HPP

#define BNS_METAL_MESH_FACTORY_HPP

#include "mesh/MeshFactory.hpp"

namespace bns
{
    /**
     * @brief A mesh factory for Metal.
     */
    class MetalMeshFactory final : public MeshFactory
    {
    public:
        MetalMeshFactory(const Framework &framework);
        ~MetalMeshFactory();

        Mesh *CreateTriangleMesh() override;
        Mesh *CreateQuadMesh(bool interleaved = true) override;
    };
}

#endif // !BNS_METAL_MESH_FACTORY_HPP