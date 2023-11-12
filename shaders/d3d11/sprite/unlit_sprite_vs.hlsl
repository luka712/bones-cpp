
cbuffer CameraConstantBuffer : register(b0)
{
    matrix c_projectionViewMatrix;
};

struct VS_INPUT
{
    float3 position : POSITION;
    float2 texCoords : TEXCOORD0;
    float4 tintColor : COLOR0;
};

struct PS_INPUT
{
    float4 position : SV_POSITION;
    float2 texCoords : TEXCOORD0;
    float3 tintColor : COLOR;
};

PS_INPUT main(VS_INPUT input)
{    
    PS_INPUT output;
    output.position = mul(float4(input.position, 1.0), c_projectionViewMatrix);
    output.texCoords = input.texCoords;
    output.tintColor = input.tintColor;
    return output;
}