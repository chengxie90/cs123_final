#include <GL/glew.h>
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
    assert(vertexArrayObject_ > 0 && vertexBufferObject_ > 0 && indexBufferObject_ > 0);
    
    glBindVertexArray(vertexArrayObject_);
    
    glDrawElements(GL_TRIANGLES, indexBuffer().size(), GL_UNSIGNED_SHORT, (void *)0);
    
    glBindVertexArray(0);
}
const VertexBuffer& Mesh::vertexBuffer() const
{
    return vertexBuffer_;
}

void Mesh::setVertexBuffer(VertexBuffer &&vertexBuffer)
{
    vertexBuffer_ = std::move(vertexBuffer);
    
    if (vertexArrayObject_ == 0) {
        glGenVertexArrays(1, &vertexArrayObject_);
    }
    
    if (vertexBufferObject_ == 0) {
        glGenBuffers(1, &vertexBufferObject_);
    }
    
    glBindVertexArray(vertexArrayObject_);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject_);
    
    glBufferData(GL_ARRAY_BUFFER, vertexBuffer_.size() * sizeof(Vertex), vertexBuffer_.data(), GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)sizeof(vec3));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(sizeof(vec3) + sizeof(vec3)));
    
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);
    
}
const IndexBuffer& Mesh::indexBuffer() const
{
    return indexBuffer_;
}

void Mesh::setIndexBuffer(IndexBuffer &&indexBuffer)
{
    indexBuffer_ = std::move(indexBuffer);
    
    if (vertexArrayObject_ == 0) {
        glGenVertexArrays(1, &vertexArrayObject_);
    }
    
    if (indexBufferObject_ == 0) {
        glGenBuffers(1, &indexBufferObject_);
    }
    
    glBindVertexArray(vertexArrayObject_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject_);
    
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBuffer_.size() * sizeof(uint16_t), indexBuffer_.data(), GL_STATIC_DRAW);
    
    glBindVertexArray(0);
}


