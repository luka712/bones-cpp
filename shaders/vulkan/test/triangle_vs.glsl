#version 450

layout(location = 0) in vec2 vertexPosition;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec2 vertexUV;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragUV;

layout(push_constant) uniform constants {
    mat4 model;
} ObjectData;

layout(binding = 0) uniform UniformBufferObject {
    mat4 proj;
} ubo;

void main() {
	gl_Position = ubo.proj * ObjectData.model * vec4(vertexPosition, 0.0, 1.0);
	fragColor = vertexColor;
	fragUV = vertexUV;
}