#version 330

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;

uniform vec3 lightDir;
uniform vec3 lightColor;

uniform mat4 view;
uniform mat4 projection;

uniform vec4 ambient;
uniform vec4 diffuse;

out vec3 n;
out vec3 l;

void main( void )
{
    l = normalize(-lightDir);
    n = normalize(normal);
    
    gl_Position = projection * view * vec4(vertex, 1);
}
