#ifndef MESH_H
#define MESH_H

#include "geometry.h"
#include "common.h"

#include "sceneobject.h"

struct SimpleVertex {
    vec3 position;
    vec3 normal;
    vec2 uv;
};

class Mesh : public SceneObject
{
public:
    Mesh();
    ~Mesh();
    
    virtual void renderGeometry(DrawContext &context) override;
    
    void load(string name);
    
    MeshRenderer *meshRenderer();
    void setMeshRenderer(MeshRenderer *meshRenderer);
    
private:
    MeshRenderer* meshRenderer_ = NULL;
};

#endif // MESH_H
