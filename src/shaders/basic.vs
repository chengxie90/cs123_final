#version 330

layout (location = 1) in vec4 vertex;

void main( void )
{
    gl_Position = vertex;
}
