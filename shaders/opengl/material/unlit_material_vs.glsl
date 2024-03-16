#version 450 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec4 a_color;
layout (location = 2) in vec2 a_texCoord;
layout (location = 3) in mat4 i_transform;

out VSOutput 
{
    vec4 color;
    vec2 texCoords;
} vsOut;

layout (std140, binding = 0) uniform TextureTilling
{
    uniform vec2 u_textureTilling;
};

layout (std140, binding = 1) uniform CameraBuffer
{
    uniform mat4 u_projectionView;
};

void main() 
{
	gl_Position = u_projectionView * i_transform * vec4(a_position, 1.0);
	vsOut.color = a_color;
	vsOut.texCoords = a_texCoord * u_textureTilling;
}