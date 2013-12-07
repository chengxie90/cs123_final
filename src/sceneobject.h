#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "common.h"
#include "material.h"
#include "geometry.h"

class SceneObject
{
public:
    SceneObject();
    virtual ~SceneObject();
    
    void render(DrawContext& context);
    
    const Material *material() const;
    void setMaterial(Material *material);
    
    mat4& transform();
    const mat4& transform() const;
    void setTransform(const mat4 &transform);
    
protected:
    virtual void renderGeometry(DrawContext& context) = 0;
    
    Material* material_;
    mat4 transform_;
};

#endif // SCENEOBJECT_H
