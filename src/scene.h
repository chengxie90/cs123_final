#ifndef SCENE_H
#define SCENE_H

#include "common.h"
#include "Tornado.h"

class Skybox;

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
    
private:
    SceneObjects sceneObjects_;
    Lights lights_;
    
    Skybox* skybox_;
    Tornado* tornado_;
    
    Color fogColor_;
    float fogDensity_;
};

#endif // SCENE_H
