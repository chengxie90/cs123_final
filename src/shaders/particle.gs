#version 330

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

uniform mat4 projection;

in float dim[];
in float rot[];

out vec2 uv;

void main() {
    float size = dim[0];
    float radian = rot[0];
    
    vec4 col1 = vec4(cos(radian), sin(radian), 0, 0);
    vec4 col2 = vec4(-sin(radian), cos(radian), 0, 0);
    vec4 col3 = vec4(0, 0, 1, 0);
    vec4 col4 = vec4(0, 0, 0, 1);
    mat4 rotMat = mat4(col1, col2, col3, col4);
    
    vec4 offset = rotMat * vec4(-size, -size, 0.0, 0.0);
    gl_Position = projection * (offset + gl_in[0].gl_Position);
    uv = vec2(0.0, 0.0);
    EmitVertex();

    offset = rotMat * vec4(size, -size, 0.0, 0.0);
    gl_Position = projection * (offset + gl_in[0].gl_Position);
    uv = vec2(1.0, 0.0);
    EmitVertex();

    offset = rotMat * vec4(-size, size, 0.0, 0.0);
    gl_Position = projection * (offset + gl_in[0].gl_Position);
    uv = vec2(0.0, 1.0);
    EmitVertex();

    offset = rotMat * vec4(size, size, 0.0, 0.0);
    gl_Position = projection * (offset + gl_in[0].gl_Position);
    uv = vec2(1.0, 1.0);
    EmitVertex();

    EndPrimitive();

}

