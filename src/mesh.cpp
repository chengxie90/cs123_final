#include "mesh.h"
#include <QFile>
#include <QTextStream>
#include <QRegExp>
#include <QStringList>
#include "meshrenderer.h"

Mesh::Mesh()
{
    
}

Mesh::~Mesh()
{
    delete meshRenderer_;
}

void Mesh::renderGeometry(DrawContext &context)
{
    assert(meshRenderer_);
    Q_UNUSED(context);
    meshRenderer_->render();
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
    
    MeshRenderer* renderer = new MeshRenderer();
    renderer->setVertexBuffer(desc, PrimitiveType::Triangles);
    renderer->setIndexBuffer(indexBuffer);
    
    setMeshRenderer(renderer);
}

MeshRenderer *Mesh::meshRenderer()
{
    return meshRenderer_;
}

void Mesh::setMeshRenderer(MeshRenderer *meshRenderer)
{
    delete meshRenderer_;
    meshRenderer_ = meshRenderer;
}


