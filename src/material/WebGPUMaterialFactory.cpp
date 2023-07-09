#include "material/WebGPUMaterialFactory.hpp"
#include "material/basic/wgpu/WebGPUBasicMaterial.hpp"

namespace bns 
{
    WebGPUMaterialFactory::WebGPUMaterialFactory(Framework& framework)
    {
        this->m_framework = &framework;
    }

    BasicMaterial *WebGPUMaterialFactory::CreateBasicMaterial()
    {
        return CreateBasicMaterial(BasicMaterialData());
    }

    BasicMaterial *WebGPUMaterialFactory::CreateBasicMaterial(BasicMaterialData options)
    {
        WebGPUBasicMaterial* material = new WebGPUBasicMaterial(*m_framework, options.MaxInstances);
        material->Initialize();

        return material;
    }
}