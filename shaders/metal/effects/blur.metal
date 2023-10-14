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

constant float weights[5] = {
    0.204163688, 
    0.180173822, 
    0.123831536, 
    0.066282245, 
    0.027630550
};

fragment 
float4 fs_main_horizontal_pass(VSOutput in [[stage_in]],
                texture2d<float, access::sample> texture [[texture(0)]],
                sampler sampler [[sampler(0)]])
{
    float horizontalTexelSize = 1.0 / float(texture.get_width(0));

    float4 result = texture.sample(sampler, in.texCoords) * weights[0];

    for(int i = 1; i < 5; i++)
    {
        float2 offset = float2(horizontalTexelSize * float(i), 0.0);

        float2 texCoordsRight = in.texCoords + offset;
        float2 texCoordsLeft = in.texCoords - offset;

        result += texture.sample(sampler, texCoordsRight) * weights[i];
        result += texture.sample(sampler, texCoordsLeft) * weights[i];
    }

    return float4(result.rgb, 1.0);
}

fragment 
float4 fs_main_vertical_pass(VSOutput in [[stage_in]],
                texture2d<float, access::sample> texture [[texture(0)]],
                sampler sampler [[sampler(0)]])
{
    float verticalTexelSize = 1.0 / float(texture.get_height(0));

    float4 result = texture.sample(sampler, in.texCoords) * weights[0];

    for(int i = 1; i < 5; i++)
    {
        float2 offset = float2(0.0, verticalTexelSize * float(i));

        float2 texCoordsUp = in.texCoords + offset;
        float2 texCoordsDown = in.texCoords - offset;

        result += texture.sample(sampler, texCoordsUp) * weights[i];
        result += texture.sample(sampler, texCoordsDown) * weights[i];
    }

    return float4(result.rgb, 1.0);
}