#include "GL/glew.h"
#include "mesh.h"
#include <QFile>
#include <QTextStream>
#include <QRegExp>
#include <QStringList>

Mesh::Mesh()
{
    
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &vertexArrayObject_);
    glDeleteBuffers(1, &vertexBufferObject_);
    glDeleteBuffers(1, &indexBufferObject_);
}

void Mesh::load(string filename)
{
    vector<SimpleVertex> vertexBuffer;
    IndexBuffer indexBuffer;
    
    vector<vec3> normals;
    vector<vec2> uvs;
    
    QFile file(filename.c_str());
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        assert(false);
        return;
    }
    
    QTextStream f(&file);
    QString line;
    
    QRegExp spaces("\\s+");
    do {
        line = f.readLine().trimmed();
        QStringList parts = line.split(spaces);
        if (parts.isEmpty()) continue;
        if (parts[0] == "v" && parts.count() >= 4) {
            float x = parts[1].toFloat();
            float y = parts[2].toFloat();
            float z = parts[3].toFloat();
            SimpleVertex v;
            v.position = {x, y, z};
            vertexBuffer.push_back(v);
        } 
        else if (parts[0] == "vn" && parts.count() >= 4) {
            float x = parts[1].toFloat();
            float y = parts[2].toFloat();
            float z = parts[3].toFloat();
            normals.push_back({x, y, z});
        }
        else if (parts[0] == "vt" && parts.count() >= 3) {
            float u = parts[1].toFloat();
            float v = parts[2].toFloat();
            uvs.push_back({u, v});
        }
        else if (parts[0] == "f" && parts.count() >= 4) {
            for (int i = 1; i <= 3; i++) {
                QStringList subparts = parts[i].split('/');
                int vertex = subparts.count() > 0 ? subparts[0].toInt() - 1 : -1;
                int uv = subparts.count() > 1 ? subparts[1].toInt() - 1 : -1;
                int normal = subparts.count() > 2 ? subparts[2].toInt() - 1 : -1;
                indexBuffer.push_back(vertex);
                SimpleVertex& v = vertexBuffer[vertex];
                if (normal != -1) {
                    v.normal += normals[normal];    
                }
                if (uv != -1) {
                    v.uv = uvs[uv];
                }
            }
        }
    } while (!line.isNull());
    
    for (SimpleVertex& v : vertexBuffer) {
        v.normal.normalize();
    }
    
    VertexBufferDesc desc;
    desc.bufferData = vertexBuffer.data();
    desc.bufferSize = vertexBuffer.size() * sizeof(SimpleVertex);
    desc.vertexElementSizes = {3, 3, 2};
    
    setVertexBuffer(desc, PrimitiveType::Triangles);
    setIndexBuffer(indexBuffer);
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


