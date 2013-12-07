#ifndef SHADERCACHE_H
#define SHADERCACHE_H

#include <resourcecache.h>
#include <QGLShaderProgram>

class ShaderCache : public ResourceCache<QGLShaderProgram>
{
public:
    static ShaderCache* getInstance();
    
private:
    virtual ~ShaderCache();
    virtual unique_ptr<QGLShaderProgram> loadResource(string name) override;
};

#endif // SHADERCACHE_H
