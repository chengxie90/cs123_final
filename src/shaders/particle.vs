#version 330

layout (location=0) in vec3 positionI;
layout (location=1) in float rotationI;
layout (location=2) in float sizeI;
layout (location=3) in vec3 colorI;
layout (location=4) in float opacityI;

uniform mat4 worldView;
uniform mat4 world;
uniform bool horizontal;

out float size;
out float rotation;
out vec3 color;
out float opacity;

uniform float fogDensity;

out float fog_factor;

void main() {
    size = sizeI;
    rotation = rotationI / 180 * 3.1415926;
    if (horizontal) {
        gl_Position = world * vec4(positionI, 1);
    }
    else {
        gl_Position = worldView * vec4(positionI, 1);
    }
    
    color = colorI;
    opacity = opacityI;

    vec4 positionV = worldView * vec4(positionI, 1);
    fog_factor = 1 - 1 / pow(exp(-positionV.z * fogDensity), 2);
}


