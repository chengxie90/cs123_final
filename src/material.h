#ifndef MATERIAL_H
#define MATERIAL_H

#include "common.h"
#include "shader.h"

class Material
{
public:
    virtual ~Material() {}
    virtual void apply(DrawContext& context) = 0;
    virtual void endRender() {}
    
protected:
    Shader *shader_ = NULL;
};

#endif // MATERIAL_H
