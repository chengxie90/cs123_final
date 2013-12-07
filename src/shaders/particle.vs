#version 330

layout (location=0) in vec3 position;
layout (location=1) in vec3 velocity;
layout (location=2) in float size;

uniform mat4 worldView;

out float dim;

void main() {
    dim = size;
    gl_Position = worldView * vec4(position, 1);
}


