#include "scene.h"
#include "material.h"
#include "directlight.h"
#include "geometry.h"
#include "mesh.h"
#include "drawcontext.h"
#include "meshcache.h"
#include "texturecache.h"

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
    Material* material = new Material("basic");
    material->setAmbient({0.2, 0.2, 0.2});
    material->setDiffuse({0.7, 0.7, 0.7});
    material->setSpecular({0.7, 0.7, 0.7});
    material->setShiness(50);
    
    Texture* diffuseMap = TextureCache::getInstance()->acquire("cheese.png");
    material->setDiffuseMap(diffuseMap);
    
    DirectLight* light = new DirectLight({-1, -0.5, -1}, {1.0, 1.0, 1.0});
    
    Mesh* mesh = MeshCache::getInstance()->acquire("sphere");
    mesh->setMaterial(material);

    sceneObjects_.push_back(mesh);
    lights_.push_back(light);
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


