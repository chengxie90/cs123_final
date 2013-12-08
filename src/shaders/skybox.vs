#version 330

layout (location=0) in vec3 position;

uniform mat4 projection;
uniform mat4 view;

out vec3 reflectDir;

void main() {
    reflectDir = position;
    mat4 v = view;
    v[3] = vec4(0, 0, 0, 1);
    gl_Position = projection * v * vec4(position * 1000, 1);
}
