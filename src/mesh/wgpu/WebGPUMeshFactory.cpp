#include "mesh/wgpu/WebGPUMeshFactory.hpp"
#include "mesh/wgpu/WebGPUMesh.hpp"
#include "Framework.hpp"

namespace bns
{
    WebGPUMeshFactory::WebGPUMeshFactory(const Framework &framework)
        : MeshFactory(framework)
    {
    }

    WebGPUMeshFactory::~WebGPUMeshFactory()
    {
    }

    Mesh *WebGPUMeshFactory::CreateTriangleMesh()
    {
        Geometry geometry = m_framework.GetGeometryBuilder().CreateTriangleGeometry();
        Mesh *mesh = new WebGPUMesh(m_framework, geometry);
        mesh->Initialize();
        return mesh;
    }
}