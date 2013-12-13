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
    
    float lengthScale() const;
    void setLengthScale(float lengthScale);
    
    float slope() const;
    void setSlope(float slope);
    
    bool horizontal() const;
    void setHorizontal(bool horizontal);
    
protected:
    Texture* texture_;
    
    bool horizontal_ = false;
    float lengthScale_ = 1;
    float slope_ = 0;
};

#endif // PARTICLEMATERIAL_H
