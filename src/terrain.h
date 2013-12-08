#ifndef TERRAIN_H
#define TERRAIN_H

#include "sceneobject.h"

class Terrain : public SceneObject
{
public:
    Terrain();
    
private:
    void buildMesh() {}
};

#endif // TERRAIN_H
