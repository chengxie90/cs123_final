#version 330

layout (location=0) in vec3 position;
layout (location=1) in float rotation;
layout (location=2) in float size;

uniform mat4 worldView;

out float dim;
out float rot;

void main() {
    dim = size;
    rot = rotation / 180 * 3.1415926;
    gl_Position = worldView * vec4(position, 1);
}


