#include <metal_stdlib>

using namespace metal;

struct VertexIn 
{
    packed_float3 position;
    packed_float2 texCoords;
    packed_float4 tintColor;
};

struct VSOutput 
{
    float4 position [[position]];
    float2 texCoords;
    float4 tintColor;
};

vertex 
VSOutput vs_main(
    const device VertexIn* in [[buffer(0)]],
    constant float4x4& u_projectionViewMatrix [[buffer(1)]],
    uint vid [[vertex_id]])
{
    VSOutput out;
    out.position = u_projectionViewMatrix * float4(in[vid].position.xyz, 1.0);
    out.texCoords = in[vid].texCoords;
    out.tintColor = in[vid].tintColor;

    return out;
}

fragment 
float4 fs_main(VSOutput in [[stage_in]],
                texture2d<float, access::sample> texture [[texture(0)]],
                sampler sampler [[sampler(0)]])
{
    float4 texColor = texture.sample(sampler, in.texCoords);
    return texColor * in.tintColor;
}
