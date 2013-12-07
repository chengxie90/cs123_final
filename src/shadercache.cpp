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

Shader *ShaderCache::acquire(string name)
{
    Shader *p = getResource(name);
    
    if (p) {
        return p;
    }
    
    string path = "shaders/";
    string vertexShader = path + name + ".vs";
    string geometryShader = path + name + ".gs";
    string fragmentShader = path + name + ".fs";
    
    p = new Shader;
    
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
    
    addResource(name, p);
    
    return p;
}

ShaderCache::~ShaderCache()
{
    delete g_instance;
}
