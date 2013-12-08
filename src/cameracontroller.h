#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include "common.h"

class QMouseEvent;
class QKeyEvent;
class QWheelEvent;

// This class is intended to be an abstract class, if we need more ways to control cameras
class CameraController
{
public:
    CameraController(Camera* camera);
    
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent *event);
    
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);
protected:
    void updateViewMatrix();
    
    Camera* camera_;
    
    QPoint oldMousePos_;
    bool mouseDragging_ = false;
    
    float angleX_ = 0;
    float angleY_ = 0;
    float zoom_ = 5;
};

#endif // CAMERACONTROLLER_H
