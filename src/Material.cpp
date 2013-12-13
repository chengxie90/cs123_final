#include <GL/glew.h>
#include "shader.h"
#include "shadercache.h"
#include "drawcontext.h"
#include "scene.h"
#include "material.h"

void Material::apply(DrawContext &context)
{
    shader_->bind();
    context.shader = shader_;
    
    shader_->setUniformValue("fogColor", context.scene->fogColor());
    shader_->setUniformValue("fogDensity", context.scene->fogDensity());
}
