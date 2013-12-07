#include "texturecache.h"

static TextureCache* g_instance = NULL;

TextureCache *TextureCache::getInstance()
{
    if (!g_instance) {
        g_instance = new TextureCache;
    }
    return g_instance;
}

TextureCache::~TextureCache()
{
    delete g_instance;
}

unique_ptr<Texture> TextureCache::loadResource(string name)
{
    string filename = "textures/" + name;
    unique_ptr<Texture> p(new Texture);
    p->load(filename);
    return p;
}
