#ifndef TERRAINMATERIAL_H
#define TERRAINMATERIAL_H

#include "material.h"

class TerrainMaterial : public Material
{
public:
    TerrainMaterial();
    
    virtual void apply(DrawContext &context) override;
    
    Texture *diffuseMap() const;
    void setDiffuseMap(Texture *diffuseMap);
    
    Texture *heightMap() const;
    void setHeightMap(Texture *heightMap);
    
    const Color& ambient() const;
    void setAmbient(const Color &ambient);
    
    float heightScale() const;
    void setHeightScale(float value);
    
private:
    Texture* diffuseMap_ = NULL;
    Texture* heightMap_ = NULL;
    
    Color ambient_;
    
    float heightScale_ = 1;
    
};

#endif // TERRAINMATERIAL_H
