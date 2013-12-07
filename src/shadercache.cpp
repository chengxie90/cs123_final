#include "shadercache.h"
#include "common.h"
#include <QFile>

static ShaderCache* g_instance = NULL;

ShaderCache *ShaderCache::getInstance()
{
    if (!g_instance) {
        g_instance = new ShaderCache;
    }
    return g_instance;
}

ShaderCache::~ShaderCache()
{
    delete g_instance;
}

unique_ptr<Shader> ShaderCache::loadResource(string shader)
{
    string path = "shaders/";
    
    string vertexShader = path + shader + ".vs";
    string geometryShader = path + shader + ".gs";
    string fragmentShader = path + shader + ".fs";
    
    unique_ptr<Shader> p(new Shader);
    
    bool result;
    
    result = p->addShaderFromSourceFile(QGLShader::Vertex, vertexShader.c_str());
    if (!result) {
        DEBUG_LOG(p->log().toStdString().c_str());
        assert(false);
    }
    
    QFile file(geometryShader.c_str());
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        result = p->addShaderFromSourceFile(QGLShader::Geometry, geometryShader.c_str());
        if (!result) {
            DEBUG_LOG(p->log().toStdString().c_str());
            assert(false);
        }
    }
    
    result = p->addShaderFromSourceFile(QGLShader::Fragment, fragmentShader.c_str());
    if (!result) {
        DEBUG_LOG(p->log().toStdString().c_str());
        assert(false);
    }
    
    result = p->link();
    if (!result) {
        DEBUG_LOG(p->log().toStdString().c_str());
        assert(false);
    }
    
    return p;
}
