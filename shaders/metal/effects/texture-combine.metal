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
                texture2d<float, access::sample> t_texture0 [[texture(0)]],
                sampler s_sampler0 [[sampler(0)]],
                texture2d<float, access::sample> t_texture1 [[texture(1)]],
                sampler s_sampler1 [[sampler(1)]],
                constant float& c_mixValue [[buffer(0)]]
                )
{
    float3 sceneTex = t_texture0.sample(s_sampler0, in.texCoords).rgb;
    float3 overlayTex = t_texture1.sample(s_sampler1, in.texCoords).rgb;

    float3 color = mix(sceneTex, overlayTex, c_mixValue);

    return float4(color, 1.0);
}
