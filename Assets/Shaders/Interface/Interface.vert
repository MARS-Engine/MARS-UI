#version 450 core

layout (location = 0) in vec3 position;

layout (binding = 0) uniform ORTHO {
	mat4 ortho;
} ortho;

void main() {
    gl_Position = ortho.ortho * vec4(position, 1.0);
}