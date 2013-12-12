#ifndef TEXTURECUBE_H
#define TEXTURECUBE_H

#include "texture.h"

class TextureCube : public Texture
{
public:
    TextureCube();
    
    virtual void load(string name) override;
    
    virtual vec4 sample(const vec3 &uvw) override;
    
    virtual void apply(DrawContext &context, string name, int binding) const override;
};

#endif // TEXTURECUBE_H
