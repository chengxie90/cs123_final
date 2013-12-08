#ifndef CAMERA_H
#define CAMERA_H

#include "geometry.h"
#include "common.h"

class Camera
{
public:
    Camera();
    virtual ~Camera() {}
    
    virtual void apply(DrawContext& context);
    
    const mat4& projectionMatrix() const;
    mat4 viewMatrix() const;
    
    void lookAt(const vec3 &eye, const vec3 &center, const vec3 &up);
    
    float near() const;
    void setNear(float near);
    
    float far() const;
    void setFar(float far);
    
    float aspectRatio() const;
    void setAspectRatio(float aspectRatio);
    
    float heightAngle() const;
    void setHeightAngle(float heightAngle);
    
    vec3 front() const;
    vec3 right() const;
    vec3 up() const;
    
    vec3 position() const;
    
    mat4& transform();
    const mat4& transform() const;
    void setTransform(const mat4 &transform);
    
private:
    void updateProjection();
    
    mat4 transform_;
    mat4 projection_;
    
    float near_;
    float far_;
    float aspectRatio_;
    float heightAngle_;
};

#endif // CAMERA_H
