#ifndef MESHCACHE_H
#define MESHCACHE_H

#include "resourcecache.h"
#include "mesh.h"

class MeshCache : public ResourceCache<Mesh>
{
public:
    static MeshCache* getInstance();
    
    Mesh* acquire(string name);
    
private:
    virtual ~MeshCache();
};

#endif // MESHCACHE_H
