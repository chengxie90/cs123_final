#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "texture.h"

class Texture2D : public Texture
{
public:
    Texture2D();
    virtual ~Texture2D();
    
    virtual void load(string filename) override;
    
    virtual vec4 sample(const vec3 &uvw) override;
    
    virtual void apply(DrawContext &context, string name, int binding) const override;
    
private:
    QImage* image_ = NULL;
};

#endif // TEXTURE2D_H
