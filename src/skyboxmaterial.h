#ifndef SKYBOXMATERIAL_H
#define SKYBOXMATERIAL_H

#include "material.h"

class SkyboxMaterial : public Material
{
public:
    SkyboxMaterial();

    void setTexture(Texture *texture);
    
    virtual void apply(DrawContext &context) override;
    
private:
    Texture* texture_;
};

#endif // SKYBOXMATERIAL_H
