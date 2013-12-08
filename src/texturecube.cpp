#include "GL/glew.h"
#include "texturecube.h"
#include "QGLWidget"
#include "drawcontext.h"

TextureCube::TextureCube()
{
}

void TextureCube::load(string name)
{
    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &textureID_);
    
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID_);
    
    const char * suffixes[] = { "+x", "-x", "+y",
                                   "-y", "+z", "-z" };
    
    GLuint targets[] = {
        GL_TEXTURE_CUBE_MAP_POSITIVE_X,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
    };
    
    for(int i = 0; i < 6; i++) {
        string path = string(name) + suffixes[i] + ".jpg";
        QImage img = QGLWidget::convertToGLFormat(QImage(path.c_str()));
        glTexImage2D(targets[i], 0  , GL_RGBA, img.width(), img.height(),
                     0, GL_RGBA, GL_UNSIGNED_BYTE, img.bits());
    }
    
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void TextureCube::apply(DrawContext &context, string name, int binding) const
{
    assert(textureID_);
    
    glActiveTexture(GL_TEXTURE0 + binding);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID_);
    
    context.shader->setUniformValue(name.c_str(), binding);
}
