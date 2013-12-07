#ifndef TEXTURECACHE_H
#define TEXTURECACHE_H

#include "texture.h"
#include "resourcecache.h"
#include "common.h"

enum class TextureType {
    Texture2D,
    TextureCube,
};

class TextureCache : public ResourceCache<Texture>
{
public:
    static TextureCache* getInstance();
    Texture* acquire(string name, TextureType type);
    
private:
    virtual ~TextureCache();
};

#endif // TEXTURECACHE_H
