#include <GL/glew.h>
#include "texture.h"
#include "drawcontext.h"
#include <QGLShaderProgram>
#include <QImage>
#include <QFile>

Texture::Texture()
{
}

Texture::~Texture()
{
    glDeleteTextures(1, &textureID_);
}

void Texture::load(string filename)
{
    QFile file(filename.c_str());

    if(!file.exists()) {
        assert(false);
        return;
    }
    
    QImage image;
    
    image.load(file.fileName());
    image = image.convertToFormat(QImage::Format_RGB32);
    
    glActiveTexture(GL_TEXTURE0);
    
    glGenTextures(1, &textureID_);
    
    glBindTexture(GL_TEXTURE_2D, textureID_);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, GL_BGRA, GL_UNSIGNED_BYTE, image.bits());
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::apply(DrawContext &context)
{
    assert(textureID_);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID_);
    
    context.shader->setUniformValue("diffuseMap", 0);
}
