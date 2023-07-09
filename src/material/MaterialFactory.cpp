#include "material/MaterialFactory.hpp"

namespace bns 
{
    BasicMaterialData::BasicMaterialData()
    {
        DiffuseColor = Color::LightGray();
        MaxInstances = 1;
    }
}