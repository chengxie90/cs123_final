#include "material.h"
#include "QString"
#include "drawcontext.h"
#include "light.h"
#include "camera.h"

Material::Material(string shader)
{
    string path = "shaders/";
    
    bool result;
    
    string vertexShader = path + shader + ".vs";
    string fragmentShader = path + shader + ".fs";
    
    result = shader_.addShaderFromSourceFile(QGLShader::Vertex, vertexShader.c_str());
    if (!result) {
        DEBUG_LOG(shader_.log().toStdString().c_str());
    }
    
    result = shader_.addShaderFromSourceFile(QGLShader::Fragment, fragmentShader.c_str());
    if (!result) {
        DEBUG_LOG(shader_.log().toStdString().c_str());
    }
    
    result = shader_.link();
    if (!result) {
        DEBUG_LOG(shader_.log().toStdString().c_str());
    }
}

void Material::apply(DrawContext &context)
{
    shader_.bind();
    context.shader = &shader_;
    
    assert(context.camera);
    
    shader_.setUniformValue("view", context.camera->getViewMatrix());
    shader_.setUniformValue("projection", context.camera->getProjectionMatrix());
    
    assert(context.light);
    context.light->apply(context);
    
    shader_.setUniformValue("ambient", ambient_);
    shader_.setUniformValue("diffuse", diffuse_);
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


