#ifndef MATERIAL_H
#define MATERIAL_H

#include "common.h"
#include <QGLShaderProgram>

class Material
{
public:
    Material(string shader);
    
    virtual void apply(DrawContext& context);
    
protected:
    QGLShaderProgram shader_;
};

#endif // MATERIAL_H
