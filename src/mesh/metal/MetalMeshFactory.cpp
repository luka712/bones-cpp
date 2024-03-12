#if USE_METAL

#include "mesh/metal/MetalMeshFactory.hpp"
#include "mesh/metal/MetalMesh.hpp"
#include "bns_framework.hpp"

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
        // TODO:
        //Geometry geometry = m_framework.GetGeometryBuilder().CreateTriangleGeometry();
        //Mesh *mesh = new MetalMesh(m_framework, geometry);
        //mesh->Initialize();
        return nullptr;
    }

    Mesh *MetalMeshFactory::CreateQuadMesh(bool interleaved)
    {
        auto geometryBuilder = m_framework.GetGeometryBuilder();

        Geometry geometry = geometryBuilder.QuadGeomtry();

        Mesh *mesh = new MetalMesh(m_framework, geometry);
        mesh->Initialize();
        return mesh;
    }
}


#endif // __APPLE__
