#include "sceneobject.h"
#include "drawcontext.h"
#include "camera.h"
#include "light.h"
#include "shader.h"
#include "mesh.h"

SceneObject::SceneObject()
{
}

SceneObject::~SceneObject()
{
    delete material_;
}

void SceneObject::render(DrawContext &context)
{
    context.currentSceneObject = this;
    
    assert(material_);
    material_->apply(context);
    
    assert(context.lights);
    for (Light* light : *context.lights) {
        light->apply(context);
    }
    
    assert(context.camera);
    context.camera->apply(context);
    
    context.shader->setUniformValue("world", transform_);
    context.shader->setUniformValue("worldView", context.camera->viewMatrix() * transform_);
    context.shader->setUniformValue("worldViewProjection",
                                    context.camera->projectionMatrix()
                                    * context.camera->viewMatrix()
                                    * transform_);
    context.shader->setUniformValue("viewInverse", context.camera->transform());
    
    renderGeometry(context);
    
    material_->endRender();
}
const Material *SceneObject::material() const
{
    return material_;
}

void SceneObject::setMaterial(Material *material)
{
    delete material_;
    material_ = material;
}

mat4 &SceneObject::transform()
{
    return transform_;
}

const mat4 &SceneObject::transform() const
{
    return transform_;
}

void SceneObject::setTransform(const mat4 &transform)
{
    transform_ = transform;
}

Mesh *SceneObject::mesh()
{
    return mesh_;
}

void SceneObject::setMesh(Mesh *mesh)
{
    mesh_ = mesh;
}

void SceneObject::renderGeometry(DrawContext &context)
{
    if (mesh_) {
        mesh_->render();
    }
}



