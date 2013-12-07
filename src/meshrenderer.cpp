#include <GL/glew.h>
#include "meshrenderer.h"

MeshRenderer::MeshRenderer()
{
    
}

MeshRenderer::~MeshRenderer()
{
    glDeleteVertexArrays(1, &vertexArrayObject_);
    glDeleteBuffers(1, &vertexBufferObject_);
    glDeleteBuffers(1, &indexBufferObject_);
}

void MeshRenderer::render() const
{
    assert(vertexArrayObject_ > 0 && vertexBufferObject_ > 0);
    assert(numElements_ > 0);
    
    glBindVertexArray(vertexArrayObject_);
    
    if (primitiveType_ == PrimitiveType::Triangles) {
        assert(indexBufferObject_ > 0);
        glDrawElements(GL_TRIANGLES, numElements_, GL_UNSIGNED_SHORT, (void *)0);
    }
    else if (primitiveType_ == PrimitiveType::Points) {
        glDrawArrays(GL_POINTS, 0, numElements_);
    }
    
    glBindVertexArray(0);
}

void MeshRenderer::setVertexBuffer(const VertexBufferDesc &vertexBuffer, PrimitiveType primitveType)
{
    primitiveType_ = primitveType;
    
    if (vertexArrayObject_ == 0) {
        glGenVertexArrays(1, &vertexArrayObject_);
    }
    
    if (vertexBufferObject_ == 0) {
        glGenBuffers(1, &vertexBufferObject_);
    }
    
    glBindVertexArray(vertexArrayObject_);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject_);
    
    glBufferData(GL_ARRAY_BUFFER, vertexBuffer.bufferSize, vertexBuffer.bufferData, GL_STATIC_DRAW);
    
    int stride = 0;
    for (uint8_t size : vertexBuffer.vertexElementSizes) {
        stride += size;
    }
    stride *= sizeof(float);
    
    if (indexBufferObject_ == 0) {
        numElements_ = vertexBuffer.bufferSize / stride;
    }
    
    uint64_t offset = 0;
    for (uint32_t i = 0; i < vertexBuffer.vertexElementSizes.size(); i++) {
        glEnableVertexAttribArray(i);
        uint32_t elementSize = vertexBuffer.vertexElementSizes[i];
        glVertexAttribPointer(i, elementSize, GL_FLOAT, GL_FALSE, stride, (void *)(offset * sizeof(float)));
        offset += elementSize;
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);
}

void MeshRenderer::setIndexBuffer(const IndexBuffer& indexBuffer)
{
    numElements_ = indexBuffer.size();
    
    if (vertexArrayObject_ == 0) {
        glGenVertexArrays(1, &vertexArrayObject_);
    }
    
    if (indexBufferObject_ == 0) {
        glGenBuffers(1, &indexBufferObject_);
    }
    
    glBindVertexArray(vertexArrayObject_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject_);
    
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBuffer.size() * sizeof(uint16_t), indexBuffer.data(), GL_STATIC_DRAW);
    
    glBindVertexArray(0);
}
