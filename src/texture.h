#ifndef TEXTURE_H
#define TEXTURE_H

#include "common.h"

class Texture
{
public:
    Texture();
    virtual ~Texture();
    
    void load(string filename);
    
    virtual void apply(DrawContext& context, string name, int binding = 0);
    
private:
    uint32_t textureID_ = 0;
};

#endif // TEXTURE_H
