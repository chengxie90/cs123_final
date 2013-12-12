#ifndef TERRAIN_H
#define TERRAIN_H

#include "sceneobject.h"

class Terrain : public SceneObject
{
public:
    Terrain(const vec3& center, int size);
    virtual ~Terrain();
};

#endif // TERRAIN_H
