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
    
    void setDiffuseMap(Texture *diffuseMap);
    Texture* getDiffuseMap(){return diffuseMap_;}
    
    // TODO
    void setHeightMap(Texture *heightMap);
    Texture* getHeightMap(){return heightMap_;}
    
private:
    Color ambient_;
    Color diffuse_;
    Color specular_;
    float shiness_ = 0;
    
    Texture* diffuseMap_ = NULL;
    
    // TODO
    Texture* heightMap_ = NULL;
};

#endif // PHONGMATERIAL_H
