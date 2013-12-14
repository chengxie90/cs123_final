#ifndef SCENE_H
#define SCENE_H

#include "common.h"
#include "geometry.h"

class Skybox;
class Cloud;
class Tornado;
class Terrain;
class PhysicsCollection;

typedef vector<SceneObject *> SceneObjects;
typedef vector<Light *> Lights;

class Scene
{
public:
    Scene();
    ~Scene();
   
    void initialize();
    
    void render(DrawContext& context);
    
    const Color& fogColor() const;
    void setFogColor(const Color &fogColor);
    
    float fogDensity() const;
    void setFogDensity(float fogDensity);
    
    void update(float dt);
    
    void pick(const vec3& point);
    
private:
    SceneObjects sceneObjects_;
    Lights lights_;

    PhysicsCollection* phys_;
    
    Skybox* skybox_;
    Tornado* tornado_;
    Cloud* follower_;
    
    Terrain* terrain_;
    
    Color fogColor_;
    float fogDensity_;
};

#endif // SCENE_H
