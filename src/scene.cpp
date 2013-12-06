#include "scene.h"
#include "material.h"
#include "directlight.h"
#include "geometry.h"
#include "mesh.h"
#include "drawcontext.h"

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
    material->setAmbient({0.3, 0.3, 0.3, 1.0});
    material->setDiffuse({0.7, 0.7, 0.7, 1.0});
    
    DirectLight* light = new DirectLight({-1, -0.5, -1}, {1.0, 1.0, 1.0, 1.0});
    
    Mesh* sphere = new Mesh();
    sphere->load("sphere");
    sphere->setMaterial(material);
    
    sceneObjects_.push_back(sphere);
    lights_.push_back(light);
}

void Scene::render(DrawContext &context)
{
    context.lights = &lights_;
    context.objects = &sceneObjects_;
    context.scene = this;
    
    for (SceneObject* object : sceneObjects_) {
        object->render(context);
    }
}


