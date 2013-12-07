#ifndef TEXTURE_H
#define TEXTURE_H

#include "common.h"

class Texture
{
public:
    Texture();
    virtual ~Texture();
    
    virtual void load(string name) = 0;
    
    virtual void apply(DrawContext& context, string name, int binding) const = 0;
    
protected:
    uint32_t textureID_ = 0;
};

#endif // TEXTURE_H
