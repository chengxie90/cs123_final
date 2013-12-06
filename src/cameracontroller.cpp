#include "cameracontroller.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include "camera.h"
#include <math.h>

CameraController::CameraController(Camera *camera)
{
    camera_ = camera;
}

void CameraController::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton) {
        oldMousePos_ = event->pos();
        mouseDragging_ = true;
    }
}

void CameraController::mouseMoveEvent(QMouseEvent *event)
{
    if (mouseDragging_) {
        QPoint mousePos = event->pos();
        QPoint deltaPos = mousePos - oldMousePos_;
        
        angleY_ += deltaPos.x();
        angleX_ += deltaPos.y();
        
        if (angleX_ < -90) angleX_ = -90;
        if (angleX_ > 90) angleX_ = 90;
        
        oldMousePos_ = mousePos;
        updateViewMatrix();
    }
}

void CameraController::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    mouseDragging_ = false;
}

void CameraController::wheelEvent(QWheelEvent *event)
{
    zoom_ *= powf(0.999f, event->delta());
    updateViewMatrix();
}

void CameraController::keyPressEvent(QKeyEvent *event)
{
    Q_UNUSED(event);
}

void CameraController::keyReleaseEvent(QKeyEvent *event)
{
    Q_UNUSED(event);
}

void CameraController::updateViewMatrix()
{
    QMatrix4x4 transform;
    transform.rotate(-angleY_, 0, 1, 0);
    transform.rotate(-angleX_, 1, 0, 0);
    transform.translate(0, 0, zoom_);
    camera_->setTransform(transform);
}
