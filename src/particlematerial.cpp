#include "particlematerial.h"
#include "shader.h"
#include "shadercache.h"
#include "drawcontext.h"
#include "texture.h"

ParticleMaterial::ParticleMaterial()
{
    shader_ = ShaderCache::getInstance()->acquire("particle");
}

void ParticleMaterial::apply(DrawContext &context)
{
    assert(texture_);
    
    Material::apply(context);
    
    texture_->apply(context, "map", 0);
    
    //glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);
}

void ParticleMaterial::endRender()
{
    //glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
}

void ParticleMaterial::setTexture(Texture *texture)
{
    texture_ = texture;
}

