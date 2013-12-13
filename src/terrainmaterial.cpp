#include "terrainmaterial.h"
#include "texture.h"
#include "drawcontext.h"
#include "shadercache.h"

TerrainMaterial::TerrainMaterial()
{
    shader_ = ShaderCache::getInstance()->acquire("terrain");
}

void TerrainMaterial::apply(DrawContext &context)
{
    assert(heightMap_);
    assert(diffuseMap_);
    
    Material::apply(context);
    
    shader_->setUniformValue("ambient", ambient_);
    shader_->setUniformValue("heightScale", heightScale_);
    
    heightMap_->apply(context, "heightMap", 0);
    diffuseMap_->apply(context, "diffuseMap", 1);
}

Texture *TerrainMaterial::diffuseMap() const
{
    return diffuseMap_;
}

void TerrainMaterial::setDiffuseMap(Texture *diffuseMap)
{
    diffuseMap_ = diffuseMap;
}

Texture *TerrainMaterial::heightMap() const
{
    return heightMap_;
}

void TerrainMaterial::setHeightMap(Texture *heightMap)
{
    heightMap_ = heightMap;
}
const Color &TerrainMaterial::ambient() const
{
    return ambient_;
}

void TerrainMaterial::setAmbient(const Color &ambient)
{
    ambient_ = ambient;
}
float TerrainMaterial::heightScale() const
{
    return heightScale_;
}

void TerrainMaterial::setHeightScale(float value)
{
    heightScale_ = value;
}




