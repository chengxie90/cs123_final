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
    
    const Color& specular() const;
    void setSpecular(const Color &specular);
    
    float shiness() const;
    void setShiness(float shiness);
    
protected:
    QGLShaderProgram shader_;
    
    Color ambient_;
    Color diffuse_;
    Color specular_;
    float shiness_ = 0;
};

#endif // MATERIAL_H
