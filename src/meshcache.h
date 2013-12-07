#ifndef MESHCACHE_H
#define MESHCACHE_H

#include "resourcecache.h"
#include "mesh.h"

class MeshCache : public ResourceCache<Mesh>
{
public:
    static MeshCache* getInstance();
    
private:
    virtual ~MeshCache();
    virtual unique_ptr<Mesh> loadResource(string name) override;
};

#endif // MESHCACHE_H
