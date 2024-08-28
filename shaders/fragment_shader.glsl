#version 460 core
out vec4 FragColor;
in vec3 color;
void main() {
    FragColor = vec3(color, 1.0f);
}