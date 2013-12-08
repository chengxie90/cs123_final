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
    
    Mesh *mesh();
    void setMesh(Mesh *mesh);
    
protected:
    virtual void renderGeometry(DrawContext& context);
    
    Mesh* mesh_ = NULL;
    Material* material_ = NULL;
    mat4 transform_;
};

#endif // SCENEOBJECT_H
