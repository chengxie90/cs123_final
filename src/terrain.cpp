#include "terrain.h"
#include "meshutility.h"
#include "phongmaterial.h"
#include "mesh.h"
#include "texturecache.h"

Terrain::Terrain()
{
    buildMesh();
}

Terrain::~Terrain()
{
    delete mesh_;
}

void Terrain::buildMesh()
{
    mesh_ = MeshUtility::createPlane(200, 200);
    
    PhongMaterial* material = new PhongMaterial;
    material->setAmbient({0.2, 0.2, 0.2});
    material->setDiffuse({0.7, 0.7, 0.2});
    
    Texture* heightMap = TextureCache::getInstance()->acquire("heightmap1", TextureType::Texture2D);
    Texture* diffuseMap = TextureCache::getInstance()->acquire("terrain", TextureType::Texture2D);
    
    material->setHeightMap(heightMap);
    material->setDiffuseMap(diffuseMap);
    
    setMaterial(material);
    
    transform().translate(0, -20, 0);
}
