#include "shadercache.h"
#include "common.h"

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

unique_ptr<QGLShaderProgram> ShaderCache::loadResource(string shader)
{
    string path = "shaders/";
    
    string vertexShader = path + shader + ".vs";
    string fragmentShader = path + shader + ".fs";
    
    unique_ptr<QGLShaderProgram> p(new QGLShaderProgram);
    
    bool result;
    
    result = p->addShaderFromSourceFile(QGLShader::Vertex, vertexShader.c_str());
    if (!result) {
        DEBUG_LOG(p->log().toStdString().c_str());
        assert(false);
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
