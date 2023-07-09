#include <metal_stdlib>

using namespace metal;

vertex 
float4 vs_main(uint vertexID [[vertex_id]])
{
    float2 positions[3];
    positions[0] = float2(0.0, 0.5);
    positions[1] = float2(-0.5, -0.5);
    positions[2] = float2(0.5, -0.5);

    return float4(positions[vertexID], 0.0, 1.0);
}

fragment 
float4 fs_main()
{
    return float4(1.0, 0.0, 0.0 ,1.0);
}
