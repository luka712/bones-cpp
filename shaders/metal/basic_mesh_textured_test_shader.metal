#include <metal_stdlib>

using namespace metal;

struct VertexIn 
{
    packed_float3 position;
    packed_float2 texCoords;
    packed_float4 color;
};

struct VSOutput 
{
    float4 position [[position]];
    float2 texCoords;
    float4 color;
};

vertex 
VSOutput vs_main(
    const device VertexIn* in [[buffer(0)]],
    uint vid [[vertex_id]])
{
    VSOutput out;
    out.position = float4(in[vid].position.xyz, 1.0);
    out.texCoords = in[vid].texCoords;
    out.color = in[vid].color;

    return out;
}

fragment 
float4 fs_main(VSOutput in [[stage_in]],
                texture2d<float, access::sample> texture [[texture(0)]],
                sampler sampler [[sampler(0)]])
{
    float4 texColor = texture.sample(sampler, in.texCoords);
    return texColor * in.color;
}
