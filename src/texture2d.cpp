#include "texture2d.h"
#include "drawcontext.h"
#include "shader.h"
#include <QImage>
#include <QFile>
#include <QGLWidget>

Texture2D::Texture2D()
{
}

Texture2D::~Texture2D()
{
    delete image_;
}

void Texture2D::load(string filename)
{
    string path = filename + ".png";
    QFile file(path.c_str());

    if(!file.exists()) {
        path = filename + ".jpg";
        file.setFileName(path.c_str());
        if (!file.exists()) {
            assert(false);
            return;
        }
    }
    
    delete image_;
    image_ = new QImage();
    
    image_->load(path.c_str());
    *image_ = QGLWidget::convertToGLFormat(*image_);
    
    glActiveTexture(GL_TEXTURE0);
    
    glGenTextures(1, &textureID_);
    
    glBindTexture(GL_TEXTURE_2D, textureID_);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_->width(), image_->height(),
                 0, GL_RGBA, GL_UNSIGNED_BYTE, image_->bits());
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glBindTexture(GL_TEXTURE_2D, 0);
}

vec4 Texture2D::sample(const vec3 &uvw)
{
    struct Color32 {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    };
    
    float u = uvw.x();
    float v = uvw.y();

    int x = (int)(u * image_->width()) % image_->width();
    int y = image_->height() - (int)(v * image_->height()) % image_->height() - 1;
    
    Color32 *data = (Color32 *)image_->bits();
    
    assert(x < image_->width() && x >= 0);
    assert(y < image_->height() && y >= 0);
    
    Color32 color = data[y * image_->width() + x];
    return vec4(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
}

void Texture2D::apply(DrawContext &context, string name, int binding) const
{
    assert(textureID_);
    
    glActiveTexture(GL_TEXTURE0 + binding);
    glBindTexture(GL_TEXTURE_2D, textureID_);
    
    context.shader->setUniformValue(name.c_str(), binding);
}
