#ifndef SHADERCACHE_H
#define SHADERCACHE_H

#include <resourcecache.h>
#include "shader.h"

class ShaderCache : public ResourceCache<Shader>
{
public:
    static ShaderCache* getInstance();
    
    Shader* acquire(string name);
    
private:
    virtual ~ShaderCache();
};

#endif // SHADERCACHE_H
