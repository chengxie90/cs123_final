#ifndef MESHUTILITY_H
#define MESHUTILITY_H

#include "common.h"
#include "geometry.h"

class MeshUtility
{
public:
    static Mesh* loadObjModel(string filename);
    
    static Mesh* createPlane(int tessellationLevel, float size);
    
    static void tessellate(vec3 p1, vec3 p2, int level, vector<vec3>& result);
};

#endif // MESHUTILITY_H
