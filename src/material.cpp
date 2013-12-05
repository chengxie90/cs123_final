#include "material.h"
#include "QString"

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
    
}
