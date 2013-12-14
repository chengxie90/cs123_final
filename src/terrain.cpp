#include "terrain.h"
#include "meshutility.h"
#include "terrainmaterial.h"
#include "mesh.h"
#include "texturecache.h"
#include "texture.h"

Terrain::Terrain(const vec3& center, float size)
{
    size_ = size;
    center_ = center;
    
    heightScale_ = 30;
    
    mesh_ = MeshUtility::createPlane(200, size);
    
    TerrainMaterial* material = new TerrainMaterial;
    material->setAmbient({0.4, 0.4, 0.4});
    
    Texture* heightMap = TextureCache::getInstance()->acquire("heightmap2", TextureType::Texture2D);
    Texture* diffuseMap = TextureCache::getInstance()->acquire("terrain", TextureType::Texture2D);
    
    material->setHeightMap(heightMap);
    material->setDiffuseMap(diffuseMap);
    
    heightMap_ = heightMap;
    
    material->setHeightScale(heightScale_);
    
    setMaterial(material);
    
    transform().translate(center);
}

Terrain::~Terrain()
{
    delete mesh_;
}

float Terrain::height(float x, float z)
{
    assert(heightMap_);
    
    vec3 uvw;

    float width = size_ * 2;
    
    uvw.setX(max(0.f, (x + size_) / width));
    uvw.setY(max(0.f, (z + size_) / width));
    uvw.setZ(0);
    
    return heightMap_->sample(uvw).x() * heightScale_;
}
