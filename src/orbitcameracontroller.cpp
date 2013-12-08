#include "orbitcameracontroller.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include "camera.h"
#include <math.h>

void OrbitCameraController::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton) {
        oldMousePos_ = event->pos();
        mouseDragging_ = true;
    }
}

void OrbitCameraController::mouseMoveEvent(QMouseEvent *event)
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

void OrbitCameraController::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    mouseDragging_ = false;
}

void OrbitCameraController::wheelEvent(QWheelEvent *event)
{
    zoom_ *= powf(0.999f, event->delta());
    updateViewMatrix();
}

void OrbitCameraController::updateViewMatrix()
{
    QMatrix4x4 transform;
    transform.rotate(-angleY_, 0, 1, 0);
    transform.rotate(-angleX_, 1, 0, 0);
    transform.translate(0, 0, zoom_);
    camera_->setTransform(transform);
}
