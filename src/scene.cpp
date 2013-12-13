#include "scene.h"
#include "phongmaterial.h"
#include "directlight.h"
#include "geometry.h"
#include "mesh.h"
#include "drawcontext.h"
#include "meshcache.h"
#include "texturecache.h"
#include "particlematerial.h"
#include "particlesystem.h"
#include "TornadoParticleSystem.h"
#include "DustcloudParticleSystem.h"
#include "skybox.h"
#include "skyboxmaterial.h"
#include "terrain.h"

Scene::Scene()
{
    initialize();
}

Scene::~Scene()
{
    for (Light* light : lights_) {
        delete light;
    }
    
    for (SceneObject* object : sceneObjects_) {
        delete object;
    }
    
    delete skybox_;
    delete tornado_;
}

void Scene::initialize()
{   
    setFogColor({0.45, 0.47, 0.5});
    setFogDensity(0.004);
    
    // Materials are owned (and deleted) by SceneObject
    PhongMaterial* material1 = new PhongMaterial;
    material1->setAmbient({0.2, 0.2, 0.2});
    material1->setDiffuse({0.7, 0.7, 0.7});
    material1->setSpecular({0.7, 0.7, 0.7});
    material1->setShiness(100);
    
    // Textures are owned by cache
    Texture* diffuseMap = TextureCache::getInstance()->acquire("cheese", TextureType::Texture2D);
    material1->setDiffuseMap(diffuseMap);
    
    SceneObject* obj1 = new SceneObject;
    Mesh* mesh1 = MeshCache::getInstance()->acquire("cube");
    obj1->setMesh(mesh1);
    obj1->setMaterial(material1);
            
    sceneObjects_.push_back(obj1);
    
    // Lights owned by the scene
    DirectLight* light = new DirectLight({-1, -0.5, -1}, {1.0, 1.0, 1.0});
    lights_.push_back(light);
    
    // Skybox
    skybox_ = new Skybox("cloudy");
    
    // Terrain
    int size = 200;
    
    Terrain* terrain = new Terrain({0, 0, 0}, size);
    sceneObjects_.push_back(terrain);
    
    float x = -100;
    float z = 100;
    float y = terrain->height(x, z);
    
    obj1->transform().translate(x, y, z);

    // Get a tornado in here!
    vec3 tornadoStart;
    tornadoStart.setX(0.0);
    tornadoStart.setY(0);
    tornadoStart.setZ(0.0);
    tornado_ = new Tornado(tornadoStart, terrain);
    tornadoStart.setX(8.0);
    tornadoStart.setZ(10.0);
    tornado_->setDestination(tornadoStart);
    TornadoParticleSystem* tPart = new TornadoParticleSystem(tornado_);
    Texture* tornadoMap = TextureCache::getInstance()->acquire("tornado", TextureType::Texture2D);
    tPart->setParticleTexture(tornadoMap);
    sceneObjects_.push_back(tPart);
    //DustcloudParticleSystem* dPart = new DustcloudParticleSystem(tornado_);
    //dPart->setParticleTexture(tornadoMap);
    //sceneObjects_.push_back(dPart);
}

void Scene::render(DrawContext &context)
{
    context.lights = &lights_;
    context.sceneObjects = &sceneObjects_;
    context.scene = this;
    
    skybox_->render(context);
    
    for (SceneObject* object : sceneObjects_) {
        object->render(context);
    }
}

const Color &Scene::fogColor() const
{
    return fogColor_;
}

void Scene::setFogColor(const Color &fogColor)
{
    fogColor_ = fogColor;
}
float Scene::fogDensity() const
{
    return fogDensity_;
}

void Scene::setFogDensity(float fogDensity)
{
    fogDensity_ = fogDensity;
}




