#ifndef PARTICLEMATERIAL_H
#define PARTICLEMATERIAL_H

#include "material.h"

class ParticleMaterial : public Material
{
public:
    ParticleMaterial();
    
    virtual void apply(DrawContext &context) override;
    virtual void endRender() override;
    
    void setTexture(Texture *texture);
    
protected:
    Texture* texture_;
};

#endif // PARTICLEMATERIAL_H
