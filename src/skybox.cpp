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
    Texture* texture = TextureCache::getInstance()->acquire("cloudy", TextureType::TextureCube);
    material->setTexture(texture);
    mesh_->setMaterial(material);
}

Skybox::~Skybox()
{
    delete mesh_;
}

void Skybox::render(DrawContext &context)
{
    mesh_->render(context);
}
