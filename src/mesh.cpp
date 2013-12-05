#include <GL/glew.h>
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

void Mesh::load(string filename)
{
    VertexBuffer vertexBuffer;
    IndexBuffer indexBuffer;
    
    vector<vec3> normals;
    vector<vec3> uvs;
    
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
            Vertex v;
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
            uvs.push_back({u, v, 0});
        }
        else if (parts[0] == "f" && parts.count() >= 4) {
            for (int i = 1; i <= 3; i++) {
                QStringList subparts = parts[i].split('/');
                int vertex = subparts.count() > 0 ? subparts[0].toInt() - 1 : -1;
                int uv = subparts.count() > 1 ? subparts[1].toInt() - 1 : -1;
                int normal = subparts.count() > 2 ? subparts[2].toInt() - 1 : -1;
                indexBuffer.push_back(vertex);
                Vertex& v = vertexBuffer[vertex];
                if (normal != -1) {
                    v.normal += normals[normal];    
                }
                if (uv != -1) {
                    v.uv = uvs[uv];
                }
            }
        }
    } while (!line.isNull());
    
    for (Vertex& v : vertexBuffer) {
        v.normal.normalize();
    }
    
    setVertexBuffer(std::move(vertexBuffer));
    setIndexBuffer(std::move(indexBuffer));
}

