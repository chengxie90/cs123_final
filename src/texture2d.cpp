#include "texture2d.h"
#include "drawcontext.h"
#include "shader.h"
#include <QImage>
#include <QFile>

Texture2D::Texture2D()
{
}

void Texture2D::load(string filename)
{
    QFile file(filename.c_str());

    if(!file.exists()) {
        assert(false);
        return;
    }
    
    QImage image;
    
    image.load(file.fileName());
    image = image.convertToFormat(QImage::Format_ARGB32);
    
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

void Texture2D::apply(DrawContext &context, string name, int binding) const
{
    assert(textureID_);
    
    glActiveTexture(GL_TEXTURE0 + binding);
    glBindTexture(GL_TEXTURE_2D, textureID_);
    
    context.shader->setUniformValue(name.c_str(), binding);
}
