#include "geometry/bns_geometry.hpp"

namespace bns
{
    Geometry::Geometry()
    {
        PositionsFormat = VertexFormat::Float32x3;
        ColorFormat = VertexFormat::Float32x4;
        TextureCoordsFormat = VertexFormat::Float32x2;
    }

    std::vector<f32> Geometry::ToInterleaved(GeometryFormat format)
    {
        std::vector<f32> interleaved;

        if (format == GeometryFormat::Pos3_Color4_TextureCoords2)
        {
            size_t count = Positions.size() / 3;
            for (u32 i = 0; i < count; i++)
            {
                PushFormat(i, Positions, PositionsFormat, interleaved, VertexFormat::Float32x3);
                PushFormat(i, Colors, ColorFormat, interleaved, VertexFormat::Float32x4);
                PushFormat(i, TextureCoords, TextureCoordsFormat, interleaved, VertexFormat::Float32x2);
            }
        }

        return interleaved;
    }

    void Geometry::PushFormat(i32 index, std::vector<f32> &source, VertexFormat sourceFormat, std::vector<f32> &destination, VertexFormat destinationFormat)
    {

        // This simply takes source format and pushes new vertices to destination format. If source format is less then destination, 0 is being push in it's place.
        f32 _0 = 0;
        f32 _1 = 0;
        f32 _2 = 0;
        f32 _3 = 0;

        if (sourceFormat == VertexFormat::Float32x1)
        {
            _0 = source[index];
        }
        else if (sourceFormat == VertexFormat::Float32x2)
        {
            _0 = source[index * 2];
            _1 = source[index * 2 + 1];
        }
        else if (sourceFormat == VertexFormat::Float32x3)
        {
            _0 = source[index * 3];
            _1 = source[index * 3 + 1];
            _2 = source[index * 3 + 2];
        }
        else if (sourceFormat == VertexFormat::Float32x4)
        {
            _0 = source[index * 4];
            _1 = source[index * 4 + 1];
            _2 = source[index * 4 + 2];
            _3 = source[index * 4 + 3];
        }

        destination.push_back(_0);
        if (destinationFormat >= VertexFormat::Float32x2)
        {
            destination.push_back(_1);
        }
        if (destinationFormat >= VertexFormat::Float32x3)
        {
            destination.push_back(_2);
        }
        if (destinationFormat >= VertexFormat::Float32x4)
        {
            destination.push_back(_3);
        }
    }
}