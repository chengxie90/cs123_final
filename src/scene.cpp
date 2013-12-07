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
    Texture* diffuseMap = TextureCache::getInstance()->acquire("cheese.png");
    material1->setDiffuseMap(diffuseMap);
    
    // Lights owned by the scene
    DirectLight* light = new DirectLight({-1, -0.5, -1}, {1.0, 1.0, 1.0});
    
    // Meshes owned by the scene
    Mesh* mesh1 = MeshCache::getInstance()->acquire("sphere");
    mesh1->setMaterial(material1);
    
    PhongMaterial* material2 = new PhongMaterial;
    material2->setAmbient({0.2, 0.2, 0.2});
    material2->setDiffuse({0.7, 0.7, 0.7});
    material2->setSpecular({0.7, 0.7, 0.7});
    material2->setShiness(50);
    
    mesh1->transform().translate(20, 0, 0);
    mesh1->transform().scale(5, 5, 5);
    
    Mesh* mesh2 = MeshCache::getInstance()->acquire("dragon");
    mesh2->setMaterial(material2);
    
    mesh2->transform().translate(-20, 0, 0);
    mesh2->transform().scale(20, 20, 20);

    sceneObjects_.push_back(mesh1);
    sceneObjects_.push_back(mesh2);
    lights_.push_back(light);
    
    ParticleSystem *particleSystem = new ParticleSystem;
    ParticleMaterial* particleMaterial = new ParticleMaterial;
    Texture* tornadoMap = TextureCache::getInstance()->acquire("tornado.png");
    
    particleMaterial->setTexture(tornadoMap);

    particleSystem->setMaterial(particleMaterial);
    
    sceneObjects_.push_back(particleSystem);
}

void Scene::render(DrawContext &context)
{
    context.lights = &lights_;
    context.sceneObjects = &sceneObjects_;
    context.scene = this;
    
    for (SceneObject* object : sceneObjects_) {
        object->render(context);
    }
}


