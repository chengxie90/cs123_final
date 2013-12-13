#version 330

uniform sampler2D map;

uniform vec3 fogColor;

in vec2 uv;
in float fogFactor;
in vec3 colorFactor;
in float alphaFactor;

out vec4 fragColor;

void main() {
    vec4 color = texture(map, uv);
    color *= vec4(colorFactor, alphaFactor);
    //fragColor = vec4(mix(color.xyz, fogColor, fogFactor), color.a);
    fragColor = color;
}
