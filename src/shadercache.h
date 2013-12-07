#ifndef SHADERCACHE_H
#define SHADERCACHE_H

#include <resourcecache.h>
#include "shader.h"

class ShaderCache : public ResourceCache<Shader>
{
public:
    static ShaderCache* getInstance();
    
private:
    virtual ~ShaderCache();
    virtual unique_ptr<Shader> loadResource(string name) override;
};

#endif // SHADERCACHE_H
