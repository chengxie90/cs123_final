#include "terrain.h"
#include "meshutility.h"
#include "terrainmaterial.h"
#include "mesh.h"
#include "texturecache.h"

Terrain::Terrain(const vec3& center, int size)
{
    mesh_ = MeshUtility::createPlane(200, size / 2);
    
    TerrainMaterial* material = new TerrainMaterial;
    material->setAmbient({0.4, 0.4, 0.4});
    
    Texture* heightMap = TextureCache::getInstance()->acquire("heightmap2", TextureType::Texture2D);
    Texture* diffuseMap = TextureCache::getInstance()->acquire("terrain", TextureType::Texture2D);
    
    material->setHeightMap(heightMap);
    material->setDiffuseMap(diffuseMap);
    
    material->setHeightScale(10);
    
    setMaterial(material);
    
    transform().translate(center);
}

Terrain::~Terrain()
{
    delete mesh_;
}
