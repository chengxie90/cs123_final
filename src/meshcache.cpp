#include "meshcache.h"
#include "meshutility.h"
#include "mesh.h"

static MeshCache* g_instance = NULL;

MeshCache *MeshCache::getInstance()
{
    if (!g_instance) {
        g_instance = new MeshCache;
    }
    return g_instance;
}

Mesh *MeshCache::acquire(string name)
{
    Mesh* p = getResource(name);
    
    if (p) {
        return p;
    }
    
    string filename = string("models/") + name + ".obj";
    
    p = MeshUtility::loadObjModel(filename);
    
    assert(p);
    
    addResource(name, p);
    
    return p;
}

MeshCache::~MeshCache()
{
    delete g_instance;
}
