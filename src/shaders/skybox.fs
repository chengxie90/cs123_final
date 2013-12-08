#version 330

in vec3 reflectDir;

uniform samplerCube cubeMap;

out vec4 fragColor;

void main() {
    fragColor = texture(cubeMap, reflectDir);
    //fragColor = vec4(1);
    //fragColor = vec4(normalize(reflectDir) * 0.5 + 0.5, 1);
}
