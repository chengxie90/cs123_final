#include <GL/glew.h>
#include "texture.h"
#include "drawcontext.h"

Texture::Texture()
{
}

Texture::~Texture()
{
    glDeleteTextures(1, &textureID_);
}
