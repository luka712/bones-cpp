#ifndef BNS_GEOMETRY_HPP

#define BNS_GEOMETRY_HPP

#include "bns_types.hpp"
#include <vector>
#include "bns_rendering_backend_types.hpp"

namespace bns
{
    /// @brief The geometry format.
    enum GeometryFormat
    {
        Pos3_Color4_TextureCoords2 = 0,
    };

    /// @brief The geometry.
    struct Geometry
    {
        /// @brief The default constructor of the geometry.
        Geometry();

        /// @brief The positions of the geometry.
        std::vector<f32> Positions;

        /// @brief The position vertex format of the geometry.
        VertexFormat PositionsFormat;

        /// @brief The colors vertices of the geometry.
        std::vector<f32> Colors;

        /// @brief The color vertex format of the geometry.
        VertexFormat ColorFormat;

        /// @brief The texture coordinates of the geometry.
        std::vector<f32> TextureCoords;

        /// @brief The texture coordinates vertex format of the geometry.
        VertexFormat TextureCoordsFormat;

        /// @brief The indices of the geometry.
        std::vector<u16> Indices;

        /// @brief Converts data of this geoemtry to interleaved buffer format.
        /// @param format The format of the geometry.
        /// @return The interleaved buffer.
        std::vector<f32> ToInterleaved(GeometryFormat format);

    private:
        /// @brief Pushes the geomtry data for index to the destination array.
        /// @param index The index of the geometry data. Or the index of the vertex.
        /// @param source The source array. Usually positions, texture coordinates or colors.
        /// @param sourceFormat The source format. 
        /// @param destination The destination array. Usually interleaved array.
        /// @param destinationFormat The destination format.
        void PushFormat(i32 index, std::vector<f32> &source, VertexFormat sourceFormat, std::vector<f32> &destination, VertexFormat destinationFormat);
    };
}

#endif