#version 330

layout (location = 0) in vec3 positionL;
layout (location = 1) in vec3 normalL;

uniform mat4 world;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 worldViewProjection;

out vec3 normalW;
out vec3 positionW;

void main()
{
    positionW = (world * vec4(positionL, 1)).xyz;
    normalW = (world * vec4(normalL, 0)).xyz;
    
    gl_Position = worldViewProjection * vec4(positionL, 1);
}
