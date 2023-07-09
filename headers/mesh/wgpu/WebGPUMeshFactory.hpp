#ifndef BNS_WEBGPU_MESH_FACTORY_HPP

#define BNS_WEBGPU_MESH_FACTORY_HPP

#include "mesh/MeshFactory.hpp"

namespace bns
{
    /**
     * @brief A mesh factory for WebGPU.
    */
    class WebGPUMeshFactory final : public MeshFactory
    {
    public:
        WebGPUMeshFactory(const Framework &framework);
        ~WebGPUMeshFactory();

        /**
         * @brief Create a triangle mesh.
        */
        Mesh *CreateTriangleMesh() override;
    };
}

#endif // !BNS_WEBGPU_MESH_FACTORY_HPP