#include "geometry/GeometryBuilder.hpp"

namespace bns
{
    Geometry GeometryBuilder::CreateTriangleGeometry()
    {
        Geometry geometry;
        geometry.VertexPositions = {
            -0.5f, -0.5f, 0.0f, // bottom left
            0.5f, -0.5f, 0.0f,  // bottom right
            0.0f, 0.5f, 0.0f,   // top
        };
        geometry.VertexPositionsStride = 12;
        geometry.Indices = {
            0, 1, 2};
        geometry.VertexColors = {
            1.0f, 0.0f, 0.0f, 1.0f, // bottom left
            0.0f, 1.0f, 0.0f, 1.0f, // bottom right
            0.0f, 0.0f, 1.0f, 1.0f  // top
        };
        geometry.VertexColorsStride = 16;

        geometry.TextureCoordinates = {
            0.0f, 0.0f, // bottom left
            1.0f, 0.0f, // bottom right
            0.5f, 1.0f  // top
        };
        geometry.TextureCoordinatesStride = 8;

        return geometry;
    }

    Geometry GeometryBuilder::CreateQuadGeometry(bool indices)
    {
        Geometry geometry;

        if (indices)
        {
            // TODO:
        }
        else
        {
            geometry.VertexPositions = {
                -0.5f, -0.5f, 0.0f, // bottom left
                0.5f, -0.5f, 0.0f,  // bottom right
                0.5f, 0.5f, 0.0f,   // top right
                0.5f, 0.5f, 0.0f,   // top right
                -0.5f, 0.5f, 0.0f,  // top left
                -0.5f, -0.5f, 0.0f, // bottom left

            };
            geometry.VertexPositionsStride = 12;
            geometry.Indices = {
                0, 1, 2, // t1
                2, 3, 0  // t2
            };
            geometry.VertexColors = {
                1.0f, 1.0f, 1.0f, 1.0f, // bottom left
                1.0f, 1.0f, 1.0f, 1.0f, // bottom right 
                1.0f, 1.0f, 1.0f, 1.0f, // top right
                1.0f, 1.0f, 1.0f, 1.0f, // top right
                1.0f, 1.0f, 1.0f, 1.0f, // top left
                1.0f, 1.0f, 1.0f, 1.0f, // bottom left
            };
            geometry.VertexColorsStride = 16;

            geometry.TextureCoordinates = {
                0.0f, 1.0f, // bottom left
                1.0f, 1.0f, // bottom right
                1.0f, 0.0f, // top right
                1.0f, 0.0f, // top right
                0.0f, 0.0f, // top left
                0.0f, 1.0f, // bottom left
            };
            geometry.TextureCoordinatesStride = 8;
        }

        return geometry;

    }
}
