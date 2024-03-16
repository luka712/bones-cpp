#version 450 core

in VSOutput 
{
    vec4 color;
    vec2 texCoords;
} fsIn;

uniform sampler2D u_diffuseSampler;


layout(std140, binding = 2) uniform Material 
{
    vec4 u_diffuseColor;
};

layout(location = 0) out vec4 o_outputColor;

void main()
{
    o_outputColor = texture(u_diffuseSampler, fsIn.texCoords) * u_diffuseColor * fsIn.color;
}