#include "meshcache.h"
#include "mesh.h"

static MeshCache* g_instance = NULL;

MeshCache *MeshCache::getInstance()
{
    if (!g_instance) {
        g_instance = new MeshCache;
    }
    return g_instance;
}

MeshCache::~MeshCache()
{
    delete g_instance;
}

unique_ptr<Mesh> MeshCache::loadResource(string name)
{
    unique_ptr<Mesh> p(new Mesh);
    
    string filename = string("models/") + name + ".obj";
    
    p->load(filename);
    
    return p;
}
