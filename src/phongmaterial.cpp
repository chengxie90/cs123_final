#include <GL/glew.h>
#include "phongmaterial.h"
#include "shader.h"
#include "shadercache.h"
#include "drawcontext.h"
#include "texture.h"

PhongMaterial::PhongMaterial()
{
    shader_ = ShaderCache::getInstance()->acquire("phong");
}

PhongMaterial::~PhongMaterial()
{
    
}

void PhongMaterial::apply(DrawContext &context)
{
    shader_->bind();
    context.shader = shader_;
    
    shader_->setUniformValue("ambient", ambient_);
    shader_->setUniformValue("diffuse", diffuse_);
    shader_->setUniformValue("specular", specular_);
    shader_->setUniformValue("shiness", shiness_);
    
    if (diffuseMap_) {
        shader_->setUniformValue("useDiffuseMap", true);
        diffuseMap_->apply(context, "diffuseMap", 0);
    }
    else {
        shader_->setUniformValue("useDiffuseMap", false);
    }
}

const Color& PhongMaterial::ambient() const
{
    return ambient_;
}

void PhongMaterial::setAmbient(const Color &ambient)
{
    ambient_ = ambient;
}

const Color &PhongMaterial::diffuse() const
{
    return diffuse_;
}

void PhongMaterial::setDiffuse(const Color &diffuse)
{
    diffuse_ = diffuse;
}
const Color &PhongMaterial::specular() const
{
    return specular_;
}

void PhongMaterial::setSpecular(const Color &specular)
{
    specular_ = specular;
}
float PhongMaterial::shiness() const
{
    return shiness_;
}

void PhongMaterial::setShiness(float shiness)
{
    shiness_ = shiness;
}

void PhongMaterial::setDiffuseMap(Texture *diffuseMap)
{
    diffuseMap_ = diffuseMap;
}
