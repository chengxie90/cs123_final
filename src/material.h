#ifndef MATERIAL_H
#define MATERIAL_H

#include "common.h"
#include <QGLShaderProgram>

class Material
{
public:
    Material(string shader);
    virtual ~Material();
    
    virtual void apply(DrawContext& context);
    
    const Color& ambient() const;
    void setAmbient(const Color &ambient);
    
    const Color& diffuse() const;
    void setDiffuse(const Color &diffuse);
    
protected:
    QGLShaderProgram shader_;
    
    Color ambient_;
    Color diffuse_;
};

#endif // MATERIAL_H
