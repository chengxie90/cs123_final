#version 330

layout (location=0) in vec3 position;

uniform mat4 worldViewProjection;

out vec3 reflectDir;

void main() {
    reflectDir = position;
    gl_Position = worldViewProjection * vec4(position, 1);
}
