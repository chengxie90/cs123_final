#include "directlight.h"
#include "drawcontext.h"
#include <QGLShaderProgram>

DirectLight::DirectLight(const vec3 &direction, const Color &color) 
    : direction_(direction),
      color_(color)
{
    
}

void DirectLight::apply(DrawContext &drawContext)
{
    drawContext.shader->setUniformValue("lightDir", direction_);
    drawContext.shader->setUniformValue("lightColor", color_);
}

const vec3 &DirectLight::direction() const
{
    return direction_;
}

void DirectLight::setDirection(const vec3 &direction)
{
    direction_ = direction;
}
const Color &DirectLight::color() const
{
    return color_;
}

void DirectLight::setColor(const Color &color)
{
    color_ = color;
}


