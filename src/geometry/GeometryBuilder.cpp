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

        geometry.Indices = {
            0, 1, 2};

        return geometry;
    }

    Geometry GeometryBuilder::CreateQuadGeometry()
    {
        Geometry geometry;

        geometry.NumOfVertices = 4;

        geometry.VertexPositionsStride = 12;
        geometry.Indices = {
            0, 1, 2, // t1
            2, 3, 0  // t2
        };

        geometry.VertexPositionsStride = 12;
        geometry.VertexPositions = {
            -0.5f, -0.5f, 0.0f, // bottom left
            0.5f, -0.5f, 0.0f,  // bottom right
            0.5f, 0.5f, 0.0f,   // top right
            -0.5f, 0.5f, 0.0f   // top left
        };

        geometry.TextureCoordinatesStride = 8;
        geometry.TextureCoordinates = {
            0.0f, 0.0f, // bottom left
            1.0f, 0.0f, // bottom right
            1.0f, 1.0f, // top right
            0.0f, 1.0f  // top left
        };

        geometry.VertexColorsStride = 16;
        geometry.VertexColors = {
            1.0f, 1.0f, 1.0f, 1.0f, // bottom left
            1.0f, 1.0f, 1.0f, 1.0f, // bottom right
            1.0f, 1.0f, 1.0f, 1.0f, // top right
            1.0f, 1.0f, 1.0f, 1.0f  // top left
        };

        geometry.Indices = {
            0, 1, 2, // t1
            2, 3, 0  // t2
        };

        return geometry;
    }

    Geometry GeometryBuilder::CreateInterleavedQuadGeometry()
    {
        Geometry geometry;
        geometry.IsInterleaved = true;

        geometry.Data = {
            // x y z             u v            r g b a
            // bottom left
            -0.5f,
            -0.5f,
            0.0f,
            0.0f,
            1.0f,
            1.0f,
            1.0f,
            1.0f,
            1.0f,

            // bottom right
            0.5f,
            -0.5f,
            0.0f,
            1.0,
            1.0f,
            1.0f,
            1.0f,
            1.0f,
            1.0f,

            // top right
            0.5f,
            0.5f,
            0.0f,
            1.0,
            0.0f,
            1.0f,
            1.0f,
            1.0f,
            1.0f,

            // top left
            -0.5f,
            0.5f,
            0.0f,
            0.0f,
            0.0f,
            1.0f,
            1.0f,
            1.0f,
            1.0f,
        };
        geometry.Stride = sizeof(float) * 9;

        geometry.Indices = {
            0, 1, 2, // t1
            2, 3, 0  // t2
        };

        return geometry;
    };
}
