#ifndef TEXTURECACHE_H
#define TEXTURECACHE_H

#include "texture.h"
#include "resourcecache.h"
#include "common.h"

class TextureCache : public ResourceCache<Texture>
{
public:
    static TextureCache* getInstance();
    
private:
    virtual ~TextureCache();
    virtual unique_ptr<Texture> loadResource(string name) override;
};

#endif // TEXTURECACHE_H
