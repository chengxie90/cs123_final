#ifndef DRAWCONTEXT_H
#define DRAWCONTEXT_H

#include "geometry.h"
#include "common.h"

class QGLShaderProgram;

class DrawContext
{
public:
    Camera* camera = NULL;
    
    QGLShaderProgram* shader = NULL;
    
    // TODO
    Light* light = NULL;
};

#endif // DRAWCONTEXT_H
