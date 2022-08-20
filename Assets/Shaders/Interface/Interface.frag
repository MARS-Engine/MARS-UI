#version 450 core

layout (location = 0) out vec4 FragColor;

layout (binding = 1) uniform COLOR {
    vec4 back_color;
} color;

void main() {
    FragColor = color.back_color;
}
