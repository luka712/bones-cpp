#pragma once

#ifndef BNS_MESH_FACTORY_HPP

#define BNS_MESH_FACTORY_HPP

#include "mesh/Mesh.hpp"

namespace bns
{
    class Framework;

    class MeshFactory
    {
    protected:
        const Framework &m_framework;

    public:
        MeshFactory(const Framework &framework);

        /**
         * @brief Create a triangle mesh.
         */
        virtual Mesh *CreateTriangleMesh() = 0;

        /**
         * @brief Create a quad mesh.
         * @param interleaved Whether the mesh is interleaved or not. By default it is interleaved.
         */
        virtual Mesh *CreateQuadMesh(bool interleaved = true) = 0;
    };
}

#endif // !BNS_MESH_FACTORY_HPP