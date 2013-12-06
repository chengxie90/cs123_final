#ifndef DRAWCONTEXT_H
#define DRAWCONTEXT_H

#include "geometry.h"
#include "common.h"
#include "scene.h"

class QGLShaderProgram;

class DrawContext
{
public:
    Camera* camera = NULL;
    
    // Currently enabled shader
    QGLShaderProgram* shader = NULL;
    
    // Time elapsed since last frame
    float deltaTime = 0;
    
    Lights* lights = NULL;
    
    SceneObjects* sceneObjects = NULL;
    
    Scene* scene = NULL;
    
    SceneObject* currentSceneObject = NULL;
};

#endif // DRAWCONTEXT_H
