#include "scene.h"
#include "phongmaterial.h"
#include "directlight.h"
#include "geometry.h"
#include "mesh.h"
#include "drawcontext.h"
#include "meshcache.h"
#include "texturecache.h"
#include "particlesystem.h"
#include "TornadoParticleSystem.h"
#include "DustcloudParticleSystem.h"
#include "skybox.h"
#include "terrain.h"
#include "cloud.h"
#include "rain.h"

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
    //delete tornado_;
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

    // Get a tornado in here!
    vec3 start = {0, 0, 0};
    tornado_ = new Tornado(start, terrain);
    vec3 dest = {18, 0, 10};
    tornado_->setDestination(dest);
    TornadoParticleSystem* tPart = new TornadoParticleSystem(tornado_);
    Texture* tornadoMap = TextureCache::getInstance()->acquire("tornado", TextureType::Texture2D);
    tPart->setParticleTexture(tornadoMap);
    sceneObjects_.push_back(tPart);

    /*DustcloudParticleSystem* dPart = new DustcloudParticleSystem(tornado_);
    Texture* dustMap = TextureCache::getInstance()->acquire("tornado", TextureType::Texture2D);
    dPart->setParticleTexture(dustMap);
    sceneObjects_.push_back(dPart);*/
    
    // Clouds
    Cloud* cloud = new Cloud(500);
    cloud->update(20);
    cloud->transform().translate(0, 80, 0);
    sceneObjects_.push_back(cloud);
    
    // Rain
    Rain* rain = new Rain(30);
    sceneObjects_.push_back(rain);
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

void Scene::update(float dt)
{
    
}




