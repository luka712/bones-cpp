#include <metal_stdlib>

using namespace metal;

struct VSOutput 
{
    float4 position [[position]];
    float4 color;
    float2 texCoords;
};

vertex 
VSOutput vs_main(
    const device packed_float3* positions [[buffer(0)]],
    const device packed_float4* colors [[buffer(1)]],
    const device packed_float2* texCoords [[buffer(2)]],
    uint vid [[vertex_id]])
{
    VSOutput out;
    out.position = float4(positions[vid].xyz, 1.0);
    out.color = colors[vid];
    out.texCoords = texCoords[vid];

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
