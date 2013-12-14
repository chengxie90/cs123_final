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
#include "SplashParticleSystem.h"
#include "PhysicsObject.h"
#include "skybox.h"
#include "terrain.h"
#include "cloud.h"
#include "rain.h"
#include "rainsplash.h"
#include "camera.h"
#include "wind.h"

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
    delete phys_;
    //delete tornado_;
}

#define NUM_PARTICLE_SYSTEMS 6

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
    Texture* diffuseMap = TextureCache::getInstance()->acquire("stone", TextureType::Texture2D);
    material1->setDiffuseMap(diffuseMap);
    
    SceneObject* obj1 = new SceneObject;
    Mesh* mesh1 = MeshCache::getInstance()->acquire("stone");
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
    terrain_ = terrain;

    // Clouds
    Cloud* cloud = new Cloud(500);
    cloud->transform().translate(0, 80, 0);
    
    // Rain
    Rain* rain = new Rain(30);
    sceneObjects_.push_back(rain);
    
    // RainSplash
    RainSplash* splash = new RainSplash(100, true, terrain);
    sceneObjects_.push_back(splash);
    
    splash = new RainSplash(100, false, terrain);
    sceneObjects_.push_back(splash);

    // Follower cloud
    follower_ = new Cloud(30);

    // Get a tornado in here!
    vec3 start = {0, 0, 0};
    tornado_ = new Tornado(start, terrain);
    follower_->transform().translate(start.x(), start.y() + tornado_->getHeight(), start.z());
    follower_->setEmissionRate(5);
    follower_->setMaxParticleCount(40);
    vec3 dest = {18, 0, 10};
    tornado_->setDestination(dest);
    TornadoParticleSystem* tPart = new TornadoParticleSystem(tornado_);
    tPart->init();
    Texture* tornadoMap = TextureCache::getInstance()->acquire("tornado2", TextureType::Texture2D);
    tPart->setParticleTexture(tornadoMap);

    DustcloudParticleSystem* dPart = new DustcloudParticleSystem(tornado_);
    dPart->init();
    Texture* dustMap = TextureCache::getInstance()->acquire("debris", TextureType::Texture2D);
    dPart->setParticleTexture(dustMap);

    SplashParticleSystem* sPart = new SplashParticleSystem(tornado_);
    sPart->init();
    Texture* splashMap = TextureCache::getInstance()->acquire("tornado", TextureType::Texture2D);
    sPart->setParticleTexture(splashMap);

    //Mesh* mesh11 = MeshCache::getInstance()->acquire("bunny");
    phys_ = new PhysicsCollection();
    phys_->gravity = 18.0;
    phys_->terrain = terrain_;

    Wind* wind = new Wind(100);
   
    sceneObjects_.push_back(cloud);
    sceneObjects_.push_back(follower_);
    sceneObjects_.push_back(tPart);
    sceneObjects_.push_back(dPart);
    sceneObjects_.push_back(sPart);
    sceneObjects_.push_back(wind);
}

void Scene::render(DrawContext &context)
{
    context.lights = &lights_;
    context.sceneObjects = &sceneObjects_;
    context.scene = this;
    
//    cout << context.camera->projectionMatrix() * 
//            context.camera->viewMatrix() * vec4(0, 0, 0, 1) << endl;
                                    
    skybox_->render(context);
    this->update(context.deltaTime);
    
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
    follower_->transform().setToIdentity();
    vec3 next = tornado_->getOrigin();
    next.setY(tornado_->getHeight());
    follower_->transform().translate(next);

    for(PhysicsObject* p : phys_->objects){
        if(p->isGravityEnabled())
            p->addVelocity({0.0, -phys_->gravity * dt, 0.0});
        // Now deal with objects picked up by the tornado/in the tornado field.
        vec3 pos = p->getWorldPosition();
        vec3 center = tornado_->interp(pos.y()) + tornado_->getOrigin();
        float fieldRange = tornado_->interpWidth(pos.y()) * 1.2;
        // An object is in the field if its distance from the center is less than fieldRange.
        // Also height less than tornado height.
        float tornadoY = tornado_->getOrigin().y();
        bool withinHeight = (pos.y() >= tornadoY && pos.y() < tornadoY + tornado_->getHeight());
        vec3 diff = pos - center;
        if(diff.length() <= fieldRange && withinHeight){
            p->setGravity(false);
            // Set the velocity of this thing...
            vec3 out = {-diff.z() - (0.5 * diff.x()), 0.0, diff.x()  - (0.5 * diff.z())};
            out.normalize();
            out *= tornado_->getForce();
            out.setY(tornado_->getHeight() / 6.0);
            p->setVelocity(out);
            p->addAngleVelocity({30 * dt, 60 * dt, 30 * dt});
        }
        else{
            p->setGravity(true);
        }
        p->update(dt);
    }
}

void Scene::pick(const vec3 &point)
{
    vec3 pt = point;
    float height = terrain_->height(pt.x(), pt.z());
    pt.setY(height);
    tornado_->setDestination(pt);
}

void Scene::placeObject(const vec3 &point)
{
    vec3 pt = point;
    float height = terrain_->height(pt.x(), pt.z());
    pt.setY(height);

    Mesh* mesh1 = MeshCache::getInstance()->acquire("bunny");
    PhongMaterial* tmat = new PhongMaterial;
    tmat->setAmbient({0.2, 0.2, 0.2});
    tmat->setDiffuse({0.7, 0.7, 0.7});
    tmat->setSpecular({0.7, 0.7, 0.7});
    tmat->setShiness(100);
    PhysicsObject* p = new PhysicsObject(phys_);
    float prad = 1.8;
    pt.setY(pt.y() + prad);
    p->setPosition(pt);
    p->setPhysicsRadius(prad);
    p->setMeshScale(5.0);
    p->setGravity(true);
    p->setMesh(mesh1);
    p->setMaterial(tmat);
    sceneObjects_.insert(sceneObjects_.end() - 4, p);
    phys_->objects.push_back(p);
}



