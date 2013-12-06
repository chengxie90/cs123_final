#include "sceneobject.h"

SceneObject::SceneObject()
{
}

void SceneObject::render(DrawContext &context)
{
    assert(material_);
    
    material_->apply(context);
    
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


