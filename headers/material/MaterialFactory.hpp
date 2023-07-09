#ifndef BNS_MATERIAL_FACTORY_HPP

#define BNS_MATERIAL_FACTORY_HPP

#include "data/Color.hpp"
#include "material/basic/BasicMaterial.hpp"

namespace bns
{
    struct BasicMaterialData
    {
        /**
         * @brief The diffuse color of the material.
         * This is the color of the material when light is shined on it.
         */
        Color DiffuseColor;

        /**
         * @brief Max instances to draw.
         * How many instances of the same mesh to draw.
         */
        i32 MaxInstances;

        BasicMaterialData();
    };

    class MaterialFactory
    {
    public:
        /**
         * @brief Create a new basic material.
         * @return BasicMaterial* The new basic material.
         */
        virtual BasicMaterial *CreateBasicMaterial() = 0;

        /**
         * @brief Create a new basic material.
         * @param options The options for the material.
         * @return BasicMaterial* The new basic material.
         */
        virtual BasicMaterial *CreateBasicMaterial(BasicMaterialData options) = 0;
    };
}

#endif