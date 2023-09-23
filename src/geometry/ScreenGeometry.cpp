#include "geometry/ScreenGeometry.hpp"

namespace bns
{
    ScreenGeometry::ScreenGeometry()
    {
        VertexPositions = {
            -1.0f, -1.0f, 0.0f, // bottom left
            1.0f, -1.0f, 0.0f,  // bottom right
            1.0f, 1.0f, 0.0f,   // top right
            -1.0f, 1.0f, 0.0f   // top left
        };

        TextureCoordinates = {
            0.0f, 0.0f, // bottom left
            1.0f, 0.0f, // bottom right
            1.0f, 1.0f, // top right
            0.0f, 1.0f  // top left
        };

        Indices = {
            0, 1, 2, // t1
            2, 3, 0  // t2
        };
    }
}