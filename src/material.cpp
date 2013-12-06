#include "material.h"
#include "QString"
#include "drawcontext.h"

Material::Material(string shader)
{
    string path = "shaders/";
    
    bool result;
    
    string vertexShader = path + shader + ".vs";
    string fragmentShader = path + shader + ".fs";
    
    result = shader_.addShaderFromSourceFile(QGLShader::Vertex, vertexShader.c_str());
    if (!result) {
        DEBUG_LOG(shader_.log().toStdString().c_str());
        assert(false);
    }
    
    result = shader_.addShaderFromSourceFile(QGLShader::Fragment, fragmentShader.c_str());
    if (!result) {
        DEBUG_LOG(shader_.log().toStdString().c_str());
        assert(false);
    }
    
    result = shader_.link();
    if (!result) {
        DEBUG_LOG(shader_.log().toStdString().c_str());
        assert(false);
    }
}

Material::~Material()
{
    
}

void Material::apply(DrawContext &context)
{
    shader_.bind();
    context.shader = &shader_;
    
    shader_.setUniformValue("ambient", ambient_);
    shader_.setUniformValue("diffuse", diffuse_);
    shader_.setUniformValue("specular", specular_);
    shader_.setUniformValue("shiness", shiness_);
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




