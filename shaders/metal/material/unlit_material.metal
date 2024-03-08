#include <metal_stdlib>
using namespace metal;


struct VSInput 
{
    packed_float3 position;
    packed_float4 color;
    packed_float2 texCoords;
};


struct VSOutput
{
    float4 position [[position]];
    float4 color;
    float2 texCoords;
};

vertex VSOutput main_vs(
                        // attributes or data per vertex
                        const device VSInput *vertexInput [[buffer(0)]],
                                
                        // constant buffer
                        constant float4x4 *transform [[buffer(1)]],
                        constant packed_float2 &textureTilling [[buffer(2)]],
                        constant float4x4 &projectionView [[buffer(3)]],
                                
                        // builtins
                        uint vid [[vertex_id]],
                        uint iid [[instance_id]]
                                )
{
    VSInput in = vertexInput[vid];
    VSOutput out;

    float4 pos = float4(in.position, 1.0);
    out.position = projectionView * transform[iid] * pos;
    out.color = in.color;
    out.texCoords = in.texCoords * textureTilling;
    return out;
}



fragment float4 main_fs(VSOutput in [[stage_in]],
                                
                                // constant buffers
                                constant packed_float4 &diffuseColor [[buffer(0)]],
                                
                                texture2d<float> diffuseTexture [[texture(0)]],
                                sampler texSampler [[sampler(0)]]
                                )
{
    return in.color * diffuseColor * diffuseTexture.sample(texSampler, in.texCoords);
}