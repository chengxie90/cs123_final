#ifndef TERRAIN_H
#define TERRAIN_H

#include "sceneobject.h"

class Terrain : public SceneObject
{
public:
    Terrain(const vec3& center, float size);
    virtual ~Terrain();
    
    float height(float x, float z);
    
private:
    // half width of terrain
    float size_ = 10;
    
    // weak reference
    Texture* heightMap_ = NULL;
    
    // TODO temp
    vec3 center_;
    
    float heightScale_ = 1;
};

#endif // TERRAIN_H
