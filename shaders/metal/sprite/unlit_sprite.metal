#include <metal_stdlib>

using namespace metal;

/// Vertex input struct
struct VertexIn 
{
    packed_float3 position;
    packed_float2 texCoords;
    packed_float4 tintColor;
};

struct VSResult 
{
    float4 position [[position]];
    float2 texCoords;
    float4 tintColor;
};

vertex
VSResult vs_main(
    // attributes
    const device VertexIn* in [[buffer(0)]],

    // constants 
    constant float4x4& c_projectionViewMatrix [[buffer(1)]],

    // builtins
    uint vid [[vertex_id]])
{
    VSResult out;
    out.position = c_projectionViewMatrix * float4(in[vid].position.xyz, 1.0);
    out.texCoords = in[vid].texCoords;
    out.tintColor = in[vid].tintColor;

    return out;
}

struct FSResult 
{
    float4 fragColor [[color(0)]];
    float4 brightnessColor [[color(1)]];
};

fragment 
FSResult fs_main(VSResult in [[stage_in]],

                // Texture 
                texture2d<float, access::sample> texture [[texture(0)]],
                sampler sampler [[sampler(0)]],

                // Constants 
                constant float& c_brightnessThreshold [[buffer(0)]]
                )
{
    FSResult out;

    out.fragColor = texture.sample(sampler, in.texCoords) * in.tintColor;

    float l = dot(out.fragColor.rgb, float3(0.299f, 0.587f, 0.114f));

    if(l > c_brightnessThreshold)
    {
        out.brightnessColor = out.fragColor;
    }
    else
    {
        out.brightnessColor = float4(0.0f, 0.0f, 0.0f,out.fragColor.a);
    }

    return out; 
}
