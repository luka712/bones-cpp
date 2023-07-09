#include <metal_stdlib>

using namespace metal;

// Include header shared between this Metal shader code and C code executing Metal API commands.
// #include "triangle_types.h"

// Vertex shader outputs and fragment shader inputs
struct RasterizerData
{
    // The [[position]] attribute of this member indicates that this value
    // is the clip space position of the vertex when this structure is
    // returned from the vertex function.
    float4 position [[position]];

    // Since this member does not have a special attribute, the rasterizer
    // interpolates its value with the values of the other triangle vertices
    // and then passes the interpolated value to the fragment shader for each
    // fragment in the triangle.
    float4 color;
};

vertex float4 vs_main(uint vertexID [[vertex_id]])
{
    float2 positions[3];
    positions[0] = float2(0.0, 0.5);
    positions[1] = float2(-0.5, -0.5);
    positions[2] = float2(0.5, -0.5);

    return float4(positions[vertexID], 0.0, 1.0);
}

fragment float4 fs_main()
{
    return float4(1.0, 0.0, 0.0 ,1.0);
}
