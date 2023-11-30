#version 400 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_texCoords;
layout(location = 2) in vec4 a_tintColor;

uniform mat4 u_projectionViewMatrix;

out vec2 v_texCoords;
out vec4 v_tintColor;

void main() {
    gl_Position = u_projectionViewMatrix * vec4(a_position, 1.0);
    v_texCoords = a_texCoords;
    v_tintColor = a_tintColor;
}