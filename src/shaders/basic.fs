#version 330

in vec4 color;

in vec3 n;
in vec3 l;

uniform vec4 diffuse;
uniform vec4 ambient;

out vec4 fragColor;

void main( void )
{
    //fragColor = vec4(1, 0, 0, 1);
    vec4 color = max(0, dot(l, n)) * diffuse;
    fragColor = color;
}
