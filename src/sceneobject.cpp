#include "sceneobject.h"
#include "drawcontext.h"
#include "camera.h"
#include "light.h"
#include <QGLShaderProgram>

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
    context.shader->setUniformValue("worldView", context.camera->getViewMatrix() * transform_);
    context.shader->setUniformValue("worldViewProjection",
                                    context.camera->getProjectionMatrix()
                                    * context.camera->getViewMatrix()
                                    * transform_);
    
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


