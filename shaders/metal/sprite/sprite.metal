// The number of point lights is defined by the user of shader
#define FORWARD_2D_NUM_OF_POINT_LIGHTS ##FORWARD_2D_NUM_OF_POINT_LIGHTS##

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
    // World position of vertex
    float3 worldPos;
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
    out.worldPos = in[vid].position.xyz;

    return out;
}

struct FSResult 
{
    float4 fragColor [[color(0)]];
    float4 brightnessColor [[color(1)]];
};

/// Ambient light struct
struct AmbientLight 
{
    packed_float4 color;
    float intensity;
};

/// Point light struct
struct PointLight 
{
    packed_float4 color; // 16b
    packed_float3 position; 
    float intensity;           // 32b
    float attenuationUnit; 
    float attenuationConstant;  
    float attenuationLinear; // 48b 
    float attenuationQuadratic;  
};

/// Calculates the diffuse amount of point light
/// Takes in a point light and world position of vertex
float3 point_light(PointLight light, float3 worldPos) 
{

    // Normal is always same for a sprite, so we can hardcode it
    float3 normal = float3(0.0, 0.0, 1.0);

    // lightDir is direction from vertex to light
    float3 lightDir = light.position - worldPos;

    // Distance from vertex to light
    float distance = length(lightDir);

    // Normalize lightDir
    lightDir = normalize(lightDir);

    // Diffuse amount of light
    float diffuseFactor = max(dot(normal, lightDir), 0.0);

    // Calculate attenuation
    float u = light.attenuationUnit;
    float c = light.attenuationConstant;
    float l = light.attenuationLinear * distance;
    float q = light.attenuationQuadratic * (distance * distance);

    float attenuation = u / (c + l + q);

    return diffuseFactor * light.color.rgb * light.intensity * attenuation;
}

fragment 
FSResult fs_main(VSResult in [[stage_in]],

                // Texture 
                texture2d<float, access::sample> texture [[texture(0)]],
                sampler sampler [[sampler(0)]],

                // Constants 
                constant float& c_brightnessThreshold [[buffer(0)]],
                constant AmbientLight& c_ambientLight [[buffer(1)]],

                // Point lights, size of array is defined by FORWARD_2D_NUM_OF_POINT_LIGHTS
                constant array<PointLight, FORWARD_2D_NUM_OF_POINT_LIGHTS>& c_pointLight [[buffer(2)]]
                )
{
    FSResult out;

    float3 ambient = c_ambientLight.color.rgb * c_ambientLight.intensity;

    float3 point = float3(0.0,0.0,0.0);
    for(int i = 0; i < FORWARD_2D_NUM_OF_POINT_LIGHTS; i++)
    {
        point += point_light(c_pointLight[i], in.worldPos);
    }

    out.fragColor = texture.sample(sampler, in.texCoords) * in.tintColor;
    out.fragColor.rgb *= (ambient + point);

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
