#include "skybox.h"
#include "mesh.h"
#include "meshcache.h"
#include "skyboxmaterial.h"
#include "texturecache.h"
#include "drawcontext.h"
#include "camera.h"

Skybox::Skybox(string name)
{
    mesh_ = MeshCache::getInstance()->acquire("skybox");
    
    SkyboxMaterial *material = new SkyboxMaterial;
    Texture* texture = TextureCache::getInstance()->acquire(name, TextureType::TextureCube);
    material->setTexture(texture);
    setMaterial(material);
    
    transform().translate(0, 0, 0);
}
