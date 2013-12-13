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
    
    shader_->setUniformValue("lengthScale", lengthScale_);
    shader_->setUniformValue("horizontal", horizontal_);
    
    mat4 slopeMatrix;
    slopeMatrix.rotate(slope_, {1, 0, 0});
    
    shader_->setUniformValue("slope", slopeMatrix);
    
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

float ParticleMaterial::lengthScale() const
{
    return lengthScale_;
}

void ParticleMaterial::setLengthScale(float lengthScale)
{
    lengthScale_ = lengthScale;
}

float ParticleMaterial::slope() const
{
    return slope_;
}

void ParticleMaterial::setSlope(float slope)
{
    slope_ = slope;
}
bool ParticleMaterial::horizontal() const
{
    return horizontal_;
}

void ParticleMaterial::setHorizontal(bool horizontal)
{
    horizontal_ = horizontal;
}








