#include "sceneobject.h"
#include "drawcontext.h"
#include "camera.h"
#include "light.h"

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
    context.shader->setUniformValue("worldViewProjection",
                                    context.camera->getProjectionMatrix()
                                    * context.camera->getViewMatrix()
                                    * transform_);
    
    renderGeometry(context);
}
const Material *SceneObject::material() const
{
    return material_;
}

void SceneObject::setMaterial(Material *material)
{
    material_ = material;
}

const mat4 &SceneObject::transform() const
{
    return transform_;
}

void SceneObject::setTransform(const mat4 &transform)
{
    transform_ = transform;
}


