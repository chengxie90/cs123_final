#ifndef DIRECTLIGHT_H
#define DIRECTLIGHT_H

#include "light.h"
#include "geometry.h"

class DirectLight : public Light
{
public:
    DirectLight(const vec3& direction, const Color& color);
    
    virtual void apply(DrawContext &drawContext) override;
    
    const vec3& direction() const;
    void setDirection(const vec3 &direction);
    
    const Color& color() const;
    void setColor(const Color &color);
    
private:
    vec3 direction_;
    Color color_;
};

#endif // DIRECTLIGHT_H
