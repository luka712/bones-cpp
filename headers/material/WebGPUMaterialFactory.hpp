#ifndef BNS_WEBGPU_MATERIAL_FACTORY_HPP

#define BNS_WEBGPU_MATERIAL_FACTORY_HPP

#include "material/MaterialFactory.hpp"

namespace bns
{
    class Framework;

    class WebGPUMaterialFactory final : public MaterialFactory
    {
    private:
        Framework *m_framework;

    public:
        WebGPUMaterialFactory(Framework &framework);

        /**
         * @brief Create a new basic material.
         * @return BasicMaterial* The new basic material.
         */
        BasicMaterial *CreateBasicMaterial() override;

        /**
         * @brief Create a new basic material.
         * @param options The options for the material.
         * @return BasicMaterial* The new basic material.
         */
        BasicMaterial *CreateBasicMaterial(BasicMaterialData options) override;
    };
}

#endif