#include <GL/glew.h>
#include "texture.h"


Texture::Texture()
{
}

Texture::~Texture()
{
    glDeleteTextures(1, &textureID_);
}
