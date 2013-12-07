#version 330

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

uniform mat4 projection;

in float dim[];

out vec2 uv;

void main() {
    float size = dim[0];
    gl_Position = projection * (vec4(-size, -size, 0.0, 0.0) + gl_in[0].gl_Position);
    uv = vec2(0.0, 0.0);
    EmitVertex();

    gl_Position = projection * (vec4(size, -size, 0.0, 0.0) + gl_in[0].gl_Position);
    uv = vec2(1.0, 0.0);
    EmitVertex();

    gl_Position = projection * (vec4(-size, size, 0.0, 0.0) + gl_in[0].gl_Position);
    uv = vec2(0.0, 1.0);
    EmitVertex();

    gl_Position = projection * (vec4(size, size, 0.0, 0.0) + gl_in[0].gl_Position);
    uv = vec2(1.0, 1.0);
    EmitVertex();

    EndPrimitive();

}

