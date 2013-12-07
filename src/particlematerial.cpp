#include "particlematerial.h"
#include <QGLShaderProgram>
#include "shadercache.h"
#include "drawcontext.h"
#include "texture.h"

ParticleMaterial::ParticleMaterial()
{
    shader_ = ShaderCache::getInstance()->acquire("particle");
}

void ParticleMaterial::apply(DrawContext &context)
{
    shader_->bind();
    context.shader = shader_;
    
    assert(texture_);
    
    texture_->apply(context, "map");
    
    glDisable(GL_DEPTH_TEST);
}

void ParticleMaterial::endRender()
{
    glEnable(GL_DEPTH_TEST);
}

void ParticleMaterial::setTexture(Texture *texture)
{
    texture_ = texture;
}

