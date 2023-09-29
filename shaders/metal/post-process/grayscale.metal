#include <metal_stdlib>

using namespace metal;

struct VertexIn 
{
    packed_float3 position;
    packed_float2 texCoords;
};

struct VSOutput 
{
    float4 position [[position]];
    float2 texCoords;
};

vertex 
VSOutput vs_main(
    const device VertexIn* in [[buffer(0)]],
    uint vid [[vertex_id]])
{
    VSOutput out;
    out.position = float4(in[vid].position.xyz, 1.0);
    out.texCoords = in[vid].texCoords;

    return out;
}

fragment 
float4 fs_main(VSOutput in [[stage_in]],
                texture2d<float, access::sample> texture [[texture(0)]],
                sampler sampler [[sampler(0)]])
{
    float3 texColor = texture.sample(sampler, in.texCoords).rgb;
    float3 grayscaleWeights = float3(0.2126, 0.7152, 0.0722);
    float luminance = dot(texColor, grayscaleWeights);
    return float4(float3(luminance), 1.0);
}
