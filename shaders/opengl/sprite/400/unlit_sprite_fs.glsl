#version 400 core

in vec2 v_texCoords;
in vec4 v_tintColor;

uniform sampler2D u_texture;

out vec4 o_fragColor;

void main()
{
    vec4 color = texture(u_texture, v_texCoords) * v_tintColor;

    // TODO: brightness for 2nd color

    o_fragColor = color;
}
