#version 330

uniform sampler2D map;

in vec2 uv;
out vec4 fragColor;

void main() {
    fragColor = texture(map, uv);
}
