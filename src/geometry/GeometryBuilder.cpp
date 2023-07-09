#include "geometry/GeometryBuilder.hpp"

namespace bns 
{
    Geometry GeometryBuilder::CreateTriangleGeometry()
    {
        Geometry geometry;
        geometry.VertexPositions = {
            -0.5f, -0.5f, 0.0f, // bottom left
            0.5f, -0.5f, 0.0f, // bottom right
            0.0f, 0.5f, 0.0f // top
        };
        geometry.Indices = {
            0, 1, 2
        };
        geometry.VertexColors = {
            1.0f, 0.0f, 0.0f, 1.0f, // bottom left
            0.0f, 1.0f, 0.0f, 1.0f, // bottom right
            0.0f, 0.0f, 1.0f, 1.0f // top
        };
        return geometry;
    }
}