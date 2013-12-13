#version 330

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

uniform mat4 projection;

uniform float lengthScale;
uniform bool horizontal;
uniform mat4 view;

in float size[];
in float rotation[];
in float fog_factor[];
in vec3 color[];
in float opacity[];

out vec2 uv;
out float fogFactor;
out vec3 colorFactor;
out float alphaFactor;

void main() {
    float size = size[0];
    float radian = rotation[0];
    
    vec4 col1 = vec4(cos(radian), sin(radian), 0, 0);
    vec4 col2 = vec4(-sin(radian), cos(radian), 0, 0);
    vec4 col3 = vec4(0, 0, 1, 0);
    vec4 col4 = vec4(0, 0, 0, 1);
    mat4 rotMat = mat4(col1, col2, col3, col4);
    
    float width = size;
    float height = size * lengthScale;
    vec4 offsets[4] = vec4[](vec4(-width, -height, 0, 0),
                             vec4(width, -height, 0, 0), 
                             vec4(-width, height, 0, 0), 
                             vec4(width, height, 0, 0));

    vec2 uvs[4] = vec2[](vec2(0, 0),
                         vec2(1, 0),
                         vec2(0, 1),
                         vec2(1, 1));

    for (int i = 0; i < 4; i++) {
        vec4 offset = rotMat * offsets[i];
        if (horizontal) {
            offset.xyz = offset.xzy;
            gl_Position = projection * view * (offset + gl_in[0].gl_Position);
        }
        else {
            gl_Position = projection * (offset + gl_in[0].gl_Position);
        }
        uv = uvs[i];
        fogFactor = fog_factor[0];
        colorFactor = color[0];
        alphaFactor = opacity[0];
        EmitVertex();
    }

    EndPrimitive();

}

