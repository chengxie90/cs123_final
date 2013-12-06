#include "camera.h"

Camera::Camera()
{
    near_ = 1;
    far_ = 30;
    aspectRatio_ = 1;
    heightAngle_ = 60;
    
    updateProjection();
    lookAt({1, 1, 1}, {0, 0, 0}, {0, 1, 0});
}

const mat4& Camera::getProjectionMatrix() const
{
    return projection_;
}

mat4 Camera::getViewMatrix() const
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

vec3 Camera::getPosition() const
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

