#include "fpscameracontroller.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include "camera.h"

FPSCameraController::FPSCameraController(Camera *camera) : CameraController(camera)
{

}

void FPSCameraController::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton) {
        rbuttonDown_ = true;
        oldMousePos_ = event->pos();
    }
}

void FPSCameraController::mouseMoveEvent(QMouseEvent *event)
{
    if (rbuttonDown_) {
        QPoint mousePos = event->pos();
        QPoint delta = mousePos - oldMousePos_;

        mat4& transform = camera_->transform();
        mat4 mat;
        vec3 position = camera_->position();
        
        mat.setToIdentity();
        mat.translate(-position);
        transform = mat * transform;
        
        mat.setToIdentity();
        mat.rotate(-delta.x() * 0.5, {0, 1, 0});
        transform = mat * transform;
        
        mat.setToIdentity();
        mat.rotate(-delta.y() * 0.5, camera_->right());
        transform = mat * transform;
        
        mat.setToIdentity();
        mat.translate(position);
        transform = mat * transform;
        
        oldMousePos_ = mousePos;
    }
}

void FPSCameraController::mouseReleaseEvent(QMouseEvent *event)
{
    rbuttonDown_ = false;
}

void FPSCameraController::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_W) {
        wPressed_ = true;
    }
    if (event->key() == Qt::Key_A) {
        aPressed_ = true;
    }
    if (event->key() == Qt::Key_S) {
        sPressed_ = true;
    }
    if (event->key() == Qt::Key_D) {
        dPressed_ = true;
    }
}

void FPSCameraController::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_W) {
        wPressed_ = false;
    }
    if (event->key() == Qt::Key_A) {
        aPressed_ = false;
    }
    if (event->key() == Qt::Key_S) {
        sPressed_ = false;
    }
    if (event->key() == Qt::Key_D) {
        dPressed_ = false;
    }
}

void FPSCameraController::update(float dt)
{
    float speedX = 0;
    float speedZ = 0;
    
    if (wPressed_) {
        speedZ = speed_;
    }
    
    if (sPressed_) {
        speedZ = -speed_;
    }
    
    if (dPressed_) {
        speedX = speed_;
    }
    
    if (aPressed_) {
        speedX = -speed_;
    }
    
    vec3 translation = speedX * camera_->right() + speedZ * camera_->front();
    translation *= dt;

    mat4 matrix;
    matrix.translate(translation);
    
    camera_->setTransform(matrix * camera_->transform());
}


