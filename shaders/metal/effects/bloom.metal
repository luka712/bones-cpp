#include <metal_stdlib>

using namespace metal;

struct VertexIn 
{
    packed_float3 position;
    packed_float2 texCoords;
};

struct VSResult 
{
    float4 position [[position]];
    float2 texCoords;
};

vertex 
VSResult vs_main(
    const device VertexIn* in [[buffer(0)]],
    uint vid [[vertex_id]])
{
    VSResult out;
    out.position = float4(in[vid].position.xyz, 1.0);
    out.texCoords = in[vid].texCoords;

    return out;
}

fragment 
float4 fs_main(VSResult in [[stage_in]],
                texture2d<float, access::sample> t_texture0 [[texture(0)]],
                sampler s_sampler0 [[sampler(0)]],
                texture2d<float, access::sample> t_texture1 [[texture(1)]],
                sampler s_sampler1 [[sampler(1)]]
                )
{
    float3 sceneTex = t_texture0.sample(s_sampler0, in.texCoords).rgb;
    float3 brightnessTex = t_texture1.sample(s_sampler1, in.texCoords).rgb;

    // darken the scene texture
    sceneTex *= (float3(1.0) - clamp(brightnessTex, float3(0.0), float3(1.0)));

    return float4(sceneTex.rgb + brightnessTex.rgb, 1.0);
}
