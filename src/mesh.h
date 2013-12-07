#ifndef MESH_H
#define MESH_H

#include <geometry.h>
#include <common.h>

#include "sceneobject.h"

struct Vertex {
    vec3 position;
    vec3 normal;
    vec3 uv;
};

typedef vector<uint16_t> IndexBuffer;
typedef vector<Vertex> VertexBuffer;

class Mesh : public SceneObject
{
public:
    Mesh();
    ~Mesh();
    
    void draw() const;
    
    // TODO
    virtual void renderGeometry(DrawContext &context) override;
    
    void load(string name);
    
    const VertexBuffer& vertexBuffer() const;
    void setVertexBuffer(VertexBuffer &&vertexBuffer);
    
    const IndexBuffer& indexBuffer() const;
    void setIndexBuffer(IndexBuffer &&indexBuffer);
    
private:
    VertexBuffer vertexBuffer_;
    IndexBuffer indexBuffer_;
    
    uint32_t vertexArrayObject_ = 0;
    uint32_t vertexBufferObject_ = 0;
    uint32_t indexBufferObject_ = 0;
};

#endif // MESH_H
