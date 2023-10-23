#include <metal_stdlib>

using namespace metal;

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
    const device VertexIn* in [[buffer(0)]],
    constant float4x4& u_projectionViewMatrix [[buffer(1)]],
    uint vid [[vertex_id]])
{
    VSResult out;
    out.position = u_projectionViewMatrix * float4(in[vid].position.xyz, 1.0);
    out.texCoords = in[vid].texCoords;
    out.tintColor = in[vid].tintColor;

    return out;
}

struct FSResult 
{
    float4 fragColor [[color(0)]];
    float4 brightnessColor [[color(1)]];
};

struct AmbientLight 
{
    float3 color;
    float intensity;
};


fragment 
FSResult fs_main(VSResult in [[stage_in]],
                texture2d<float, access::sample> texture [[texture(0)]],
                sampler sampler [[sampler(0)]],
                constant float& u_brightnessThreshold [[buffer(0)]],
                constant AmbientLight& u_ambientLight [[buffer(1)]])
{
    FSResult out;

    float3 ambient = u_ambientLight.color * u_ambientLight.intensity;

    out.fragColor = texture.sample(sampler, in.texCoords) * in.tintColor;
    out.fragColor.rgb *= ambient;

    float l = dot(out.fragColor.rgb, float3(0.299f, 0.587f, 0.114f));

    if(l > u_brightnessThreshold)
    {
        out.brightnessColor = out.fragColor;
    }
    else
    {
        out.brightnessColor = float4(0.0f, 0.0f, 0.0f,out.fragColor.a);
    }

    return out; 
}
