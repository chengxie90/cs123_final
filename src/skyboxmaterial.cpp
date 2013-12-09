#include "skybox.h"
#include "skyboxmaterial.h"
#include "shader.h"
#include "shadercache.h"
#include "drawcontext.h"
#include "texture.h"

SkyboxMaterial::SkyboxMaterial()
{
    shader_ = ShaderCache::getInstance()->acquire("skybox");
}

void SkyboxMaterial::setTexture(Texture *texture)
{
    texture_ = texture;
}

void SkyboxMaterial::apply(DrawContext &context)
{
    shader_->bind();
    context.shader = shader_;
    
    assert(texture_);
    
    texture_->apply(context, "cubeMap", 0);
    
    glDepthMask(GL_FALSE);
}

void SkyboxMaterial::endRender()
{
    glDepthMask(GL_TRUE);
}

