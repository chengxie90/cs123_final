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
    // Materials are owned (and deleted) by SceneObject
    PhongMaterial* material1 = new PhongMaterial;
    material1->setAmbient({0.2, 0.2, 0.2});
    material1->setDiffuse({0.7, 0.7, 0.7});
    material1->setSpecular({0.7, 0.7, 0.7});
    material1->setShiness(50);
    
    // Textures are owned by cache
    Texture* diffuseMap = TextureCache::getInstance()->acquire("frostmourne", TextureType::Texture2D);
    material1->setDiffuseMap(diffuseMap);
    
    SceneObject* obj1 = new SceneObject;
    Mesh* mesh1 = MeshCache::getInstance()->acquire("frostmourne");
    obj1->setMesh(mesh1);
    obj1->setMaterial(material1);
    
    obj1->transform().translate(20, 20, 0);
    obj1->transform().scale(20, 20, 20);
            
    sceneObjects_.push_back(obj1);       
    
    //
    PhongMaterial* material2 = new PhongMaterial;
    material2->setAmbient({0.2, 0.2, 0.2});
    material2->setDiffuse({0.7, 0.7, 0.7});
    material2->setSpecular({0.7, 0.7, 0.7});
    material2->setShiness(50);
    
    SceneObject *obj2 = new SceneObject;
    Mesh* mesh2 = MeshCache::getInstance()->acquire("bunny");
    obj2->setMesh(mesh2);
    
    obj2->setMaterial(material2);
    
    obj2->transform().translate(-20, 0, 0);
    obj2->transform().scale(20, 20, 20);

    sceneObjects_.push_back(obj2);
    
    // Lights owned by the scene
    DirectLight* light = new DirectLight({-1, -0.5, -1}, {1.0, 1.0, 1.0});
    lights_.push_back(light);
    
    // Skybox
    skybox_ = new Skybox("cloudy");
    
    // Terrain
    int size = 800;
    
    Terrain* terrain = new Terrain({0, 0, 0}, size+2);
    sceneObjects_.push_back(terrain);
    
//    terrain = new Terrain({size, 0, size}, size+2);
//    sceneObjects_.push_back(terrain);
    
//    terrain = new Terrain({size, 0, 0}, size+2);
//    sceneObjects_.push_back(terrain);

    // Get a tornado in here!
    vec3 tornadoStart;
    tornadoStart.setX(0.0);
    tornadoStart.setY(50);
    tornadoStart.setZ(0.0);
    tornado_ = new Tornado(tornadoStart);
    tornadoStart.setX(8.0);
    tornadoStart.setZ(10.0);
    tornado_->setDestination(tornadoStart);
    TornadoParticleSystem* tPart = new TornadoParticleSystem(tornado_);
    Texture* tornadoMap = TextureCache::getInstance()->acquire("tornado", TextureType::Texture2D);
    tPart->setParticleTexture(tornadoMap);
    sceneObjects_.push_back(tPart);
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


