#include "mesh/Mesh.hpp"
#include "material/Material.hpp"

namespace bns
{

    Mesh::Mesh(const Framework &framework) : m_framework(framework)
    {
        Transform = Mat4x4f::Identity();
    }

    Mesh::~Mesh()
    {
       Delete();
    }

    void Mesh::AddMaterial(Material *material)
    {
        Materials.push_back(material);
    }

    void Mesh::Draw(const Camera &camera)
    {
        for (auto material : Materials)
        {
            material->Draw(camera, this);
        }
    }

    void Mesh::Delete()
    {
         for (auto material : Materials)
        {
            if(material != nullptr)
            {
                // TODO: 
                // material->Delete();
                // delete material;
            }
        }
    }
}