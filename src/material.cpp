#include "material.h"
#include "drawcontext.h"
#include "texture.h"
#include "shadercache.h"
#include <QGLShaderProgram>

Material::Material(string shader)
{
    shader_ = ShaderCache::getInstance()->acquire(shader);
}

Material::~Material()
{
    
}

void Material::apply(DrawContext &context)
{
    shader_->bind();
    context.shader = shader_;
    
    shader_->setUniformValue("ambient", ambient_);
    shader_->setUniformValue("diffuse", diffuse_);
    shader_->setUniformValue("specular", specular_);
    shader_->setUniformValue("shiness", shiness_);
    
    if (diffuseMap_) {
        shader_->setUniformValue("useDiffuseMap", true);
        diffuseMap_->apply(context);
    }
    else {
        shader_->setUniformValue("useDiffuseMap", false);
    }
}

const Color& Material::ambient() const
{
    return ambient_;
}

void Material::setAmbient(const Color &ambient)
{
    ambient_ = ambient;
}

const Color &Material::diffuse() const
{
    return diffuse_;
}

void Material::setDiffuse(const Color &diffuse)
{
    diffuse_ = diffuse;
}
const Color &Material::specular() const
{
    return specular_;
}

void Material::setSpecular(const Color &specular)
{
    specular_ = specular;
}
float Material::shiness() const
{
    return shiness_;
}

void Material::setShiness(float shiness)
{
    shiness_ = shiness;
}
const Texture *Material::diffuseMap() const
{
    return diffuseMap_;
}

void Material::setDiffuseMap(Texture *diffuseMap)
{
    diffuseMap_ = diffuseMap;
}





