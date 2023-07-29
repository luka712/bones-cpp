#include "mesh/metal/MetalMeshFactory.hpp"
#include "mesh/metal/MetalMesh.hpp"
#include "Framework.hpp"

namespace bns
{
    MetalMeshFactory::MetalMeshFactory(const Framework &framework)
        : MeshFactory(framework)
    {
    }

    MetalMeshFactory::~MetalMeshFactory()
    {
    }

    Mesh *MetalMeshFactory::CreateTriangleMesh()
    {
        Geometry geometry = m_framework.GetGeometryBuilder().CreateTriangleGeometry();
        Mesh *mesh = new MetalMesh(m_framework, geometry);
        mesh->Initialize();
        return mesh;
    }

    Mesh *MetalMeshFactory::CreateQuadMesh(bool interleaved)
    {
        auto geometryBuilder = m_framework.GetGeometryBuilder();

        Geometry geometry = interleaved
                                ? geometryBuilder.CreateInterleavedQuadGeometry()
                                : geometryBuilder.CreateQuadGeometry();

        Mesh *mesh = new MetalMesh(m_framework, geometry);
        mesh->Initialize();
        return mesh;
    }
}
