#version 330

layout (location = 0) in vec3 positionL;
layout (location = 2) in vec2 uvL;

uniform mat4 world;
uniform mat4 worldViewProjection;

uniform float heightScale;

uniform sampler2D heightMap;

out vec3 normalW;
out vec3 positionW;
out vec2 uv;

void main()
{
    vec3 position = positionL;
    vec3 normal = vec3(0, 1, 0);

    float height = texture(heightMap, uvL).x;
    position += normal * height * heightScale;

    float turbulence = 0.1;
    const ivec3 off = ivec3(-1, 0, 1);

    float h_pos_u = textureOffset(heightMap, uvL, off.zy).x;
    float h_neg_u = textureOffset(heightMap, uvL, off.xy).x;
    float h_pos_v = textureOffset(heightMap, uvL, off.yz).x;
    float h_neg_v = textureOffset(heightMap, uvL, off.yx).x;
    vec3 du = normalize(vec3(turbulence, h_pos_u - h_neg_u, 0));
    vec3 dv = normalize(vec3(0, h_pos_v - h_neg_v, -turbulence));
    normal = cross(du, dv);

    positionW = (world * vec4(position, 1)).xyz;
    normalW = (world * vec4(normal, 0)).xyz;
    uv = uvL;

    gl_Position = worldViewProjection * vec4(position, 1);
}
