#ifndef MESHRENDERER_H
#define MESHRENDERER_H

#include "common.h"

struct VertexBufferDesc
{
    const void* bufferData;
    uint32_t bufferSize;
    vector<uint8_t> vertexElementSizes;
};

typedef vector<uint16_t> IndexBuffer;

enum class PrimitiveType 
{
    Points,
    Lines,
    Triangles,
    Patches,
};

class MeshRenderer
{
public:
    MeshRenderer();
    ~MeshRenderer();
    
    void render() const;
    
    // MeshRenderer doesn't own vertex buffer and index buffer, callers are responsible for releasing them
    void setVertexBuffer(const VertexBufferDesc& vertexBuffer, PrimitiveType primitveType);
   
    void setIndexBuffer(const IndexBuffer& indexBuffer);
    
private:
    uint32_t vertexArrayObject_ = 0;
    uint32_t vertexBufferObject_ = 0;
    uint32_t indexBufferObject_ = 0;
    PrimitiveType primitiveType_ = PrimitiveType::Triangles;
    int numElements_ = 0;
};

#endif // MESHRENDERER_H
