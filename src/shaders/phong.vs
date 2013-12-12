#version 330

layout (location = 0) in vec3 positionL;
layout (location = 1) in vec3 normalL;
layout (location = 2) in vec2 uvL;

uniform mat4 world;
uniform mat4 worldViewProjection;

out vec3 normalW;
out vec3 positionW;
out vec2 uv;

void main()
{
    vec3 position = positionL;
    vec3 normal = normalL;

    positionW = (world * vec4(position, 1)).xyz;
    normalW = (world * vec4(normal, 0)).xyz;
    uv = uvL;

    gl_Position = worldViewProjection * vec4(position, 1);
}
