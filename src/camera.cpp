#include "camera.h"
#include "drawcontext.h"
#include "shader.h"

Camera::Camera()
{
    near_ = 1;
    far_ = 10000;
    aspectRatio_ = 1;
    heightAngle_ = 60;
    
    updateProjection();
    lookAt({-100, 20, 100}, {0, 0, 0}, {0, 1, 0});
}

void Camera::apply(DrawContext &context)
{
    context.shader->setUniformValue("view", viewMatrix());
    context.shader->setUniformValue("projection", projectionMatrix());
    context.shader->setUniformValue("eyePositionW", position());
}

const mat4& Camera::projectionMatrix() const
{
    return projection_;
}

mat4 Camera::viewMatrix() const
{
    return transform_.inverted();
}

void Camera::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up)
{
    transform_.setToIdentity();
    transform_.lookAt(eye, center, up);
    transform_ = transform_.inverted();
}

void Camera::updateProjection()
{
    projection_.setToIdentity();
    projection_.perspective(heightAngle_, aspectRatio_, near_, far_);
}
const mat4 &Camera::transform() const
{
    return transform_;
}

void Camera::setTransform(const mat4 &transform)
{
    transform_ = transform;
}

float Camera::heightAngle() const
{
    return heightAngle_;
}

void Camera::setHeightAngle(float heightAngle)
{
    heightAngle_ = heightAngle;
    updateProjection();
}

vec3 Camera::front() const
{
    return -(transform_.column(2).toVector3D());
}

vec3 Camera::right() const
{
    return transform_.column(0).toVector3D();
}

vec3 Camera::up() const
{
    return transform_.column(1).toVector3D();
}

vec3 Camera::position() const
{
    return transform_.column(3).toVector3D();
}

mat4 &Camera::transform()
{
    return transform_;
}

float Camera::aspectRatio() const
{
    return aspectRatio_;
}

void Camera::setAspectRatio(float aspectRatio)
{
    aspectRatio_ = aspectRatio;
    updateProjection();
}

float Camera::far() const
{
    return far_;
}

void Camera::setFar(float far)
{
    far_ = far;
    updateProjection();
}

float Camera::near() const
{
    return near_;
}

void Camera::setNear(float near)
{
    near_ = near;
    updateProjection();
}

