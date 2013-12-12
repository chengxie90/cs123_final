#include "meshutility.h"
#include <QFile>
#include <QTextStream>
#include <QRegExp>
#include <QStringList>
#include "mesh.h"

Mesh *MeshUtility::loadObjModel(string filename)
{
    vector<SimpleVertex> vertexBuffer;
    IndexBuffer indexBuffer;
    
    vector<vec3> normals;
    vector<vec2> uvs;
    
    QFile file(filename.c_str());
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        assert(false);
        return NULL;
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
    
    Mesh* mesh = new Mesh;
    
    VertexBufferDesc desc;
    desc.bufferData = vertexBuffer.data();
    desc.bufferSize = vertexBuffer.size() * sizeof(SimpleVertex);
    desc.vertexElementSizes = {3, 3, 2};
    desc.stride = sizeof(SimpleVertex);
    
    mesh->setVertexBuffer(desc, PrimitiveType::Triangles);
    mesh->setIndexBuffer(indexBuffer);
    
    return mesh;
}

Mesh *MeshUtility::createPlane(int tessellationLevel, float size)
{
    assert(tessellationLevel > 0);
    assert(size > 0);
    
    vector<SimpleVertex> vertexBuffer;
    IndexBuffer indexBuffer;
    
    vec3 normal = {0, 1, 0};
    
    vec3 upperleft = {-size, 0, -size};
    vec3 lowerleft = {-size, 0, size};
    vec3 lowerright = {size, 0, size};
    
    vec3 dy = (upperleft - lowerleft) / tessellationLevel;
    
    float width = (lowerright - lowerleft).length();
    float height = (upperleft - lowerleft).length();
    
    // build vertices
    for (int row = 0; row <= tessellationLevel; row++) {
        vector<vec3> result;
        tessellate(lowerleft + dy * row, lowerright + dy * row, tessellationLevel, result);
        for (const vec3& point : result) {
            SimpleVertex v;
            v.position = point;
            v.normal = normal;
            v.uv.setX(vec3::dotProduct(point - lowerleft, (lowerright - lowerleft).normalized()) / width);
            v.uv.setY(vec3::dotProduct(point - lowerleft, (upperleft - lowerleft).normalized()) / height);
            vertexBuffer.push_back(v);
        }
    }
    
    // build faces
    for (int l = 0; l < tessellationLevel; l++) {
        for (int s = 0; s < tessellationLevel; s++) {
            uint16_t i1 = l * (tessellationLevel+1) + s;
            uint16_t i2 = i1 + 1;
            uint16_t i3 = i1 + tessellationLevel+1;
            uint16_t i4 = i2 + tessellationLevel+1;
            
            indexBuffer.push_back(i1);
            indexBuffer.push_back(i2);
            indexBuffer.push_back(i3);
            
            indexBuffer.push_back(i4);
            indexBuffer.push_back(i3);
            indexBuffer.push_back(i2);
        }
    }
    
    Mesh* mesh = new Mesh;
    VertexBufferDesc desc;
    desc.bufferData = vertexBuffer.data();
    desc.bufferSize = vertexBuffer.size() * sizeof(SimpleVertex);
    desc.vertexElementSizes = {3, 3, 2};
    desc.stride = sizeof(SimpleVertex);
    
    mesh->setVertexBuffer(desc, PrimitiveType::Triangles);
    mesh->setIndexBuffer(indexBuffer);
    
    return mesh;
    
}

void MeshUtility::tessellate(vec3 p1, vec3 p2, int level, vector<vec3> &result)
{
    assert(level > 0);
    
    auto delta = (p2 - p1) / level;
  
    for (int i = 0; i <= level; i++)
    {
        result.push_back(p1 + delta * i);
    }
}
