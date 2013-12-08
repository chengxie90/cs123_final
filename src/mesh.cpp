#include "GL/glew.h"
#include "mesh.h"


Mesh::Mesh()
{
    
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &vertexArrayObject_);
    glDeleteBuffers(1, &vertexBufferObject_);
    glDeleteBuffers(1, &indexBufferObject_);
}

void Mesh::render() const
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

void Mesh::setVertexBuffer(const VertexBufferDesc &vertexBuffer, PrimitiveType primitveType)
{
    assert(vertexBuffer.bufferData);
    assert(vertexBuffer.bufferSize);
    assert(vertexBuffer.stride);
    
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
    
    if (indexBufferObject_ == 0) {
        numElements_ = vertexBuffer.bufferSize / vertexBuffer.stride;
    }
    
    uint64_t offset = 0;
    for (uint32_t i = 0; i < vertexBuffer.vertexElementSizes.size(); i++) {
        glEnableVertexAttribArray(i);
        uint32_t elementSize = vertexBuffer.vertexElementSizes[i];
        glVertexAttribPointer(i, elementSize, GL_FLOAT, GL_FALSE, vertexBuffer.stride, (void *)(offset * sizeof(float)));
        offset += elementSize;
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);
}

void Mesh::setIndexBuffer(const IndexBuffer& indexBuffer)
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


