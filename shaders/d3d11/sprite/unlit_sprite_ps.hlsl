struct PS_INPUT
{
    float4 position : SV_POSITION;
    float2 texCoords : TEXCOORD0;
    float4 tintColor : COLOR;
};


sampler s_sampler : register(s0);
Texture2D<float4> t_texture : register(t0);


float4 main(PS_INPUT input) : SV_TARGET
{
    float4 color = t_texture.Sample(s_sampler, input.texCoords) * input.tintColor;

    // TODO: brightness for 2nd color

    return color;
}