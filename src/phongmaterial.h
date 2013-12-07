#ifndef PHONGMATERIAL_H
#define PHONGMATERIAL_H

#include "material.h"

class PhongMaterial : public Material
{
public:
    PhongMaterial();
    virtual ~PhongMaterial();
    
    virtual void apply(DrawContext &context) override;
    
    const Color& ambient() const;
    void setAmbient(const Color &ambient);
    
    const Color& diffuse() const;
    void setDiffuse(const Color &diffuse);
    
    const Color& specular() const;
    void setSpecular(const Color &specular);
    
    float shiness() const;
    void setShiness(float shiness);
    
    const Texture *diffuseMap() const;
    void setDiffuseMap(Texture *diffuseMap);
    
private:
    Color ambient_;
    Color diffuse_;
    Color specular_;
    float shiness_ = 0;
    
    Texture* diffuseMap_ = NULL;
};

#endif // PHONGMATERIAL_H
