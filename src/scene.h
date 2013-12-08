#ifndef SCENE_H
#define SCENE_H

#include "common.h"

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
    
private:
    SceneObjects sceneObjects_;
    Lights lights_;
    
    Skybox* skybox_;
};

#endif // SCENE_H
