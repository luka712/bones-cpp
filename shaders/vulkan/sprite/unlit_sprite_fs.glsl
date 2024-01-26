#version 450 core

layout(location = 0) in vec2 v_texCoords;
layout(location = 1) in vec4 v_tintColor;

layout(binding = 1) uniform sampler2D u_texture;

layout(location = 0) out vec4 o_fragColor;

void main()
{
    vec4 color = texture(u_texture, v_texCoords) * v_tintColor;

    // TODO: brightness for 2nd color

    o_fragColor = color;
}
