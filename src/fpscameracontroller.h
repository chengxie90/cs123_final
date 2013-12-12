#ifndef FPSCAMERACONTROLLER_H
#define FPSCAMERACONTROLLER_H

#include "cameracontroller.h"

class FPSCameraController : public CameraController
{
public:
    FPSCameraController(Camera* camera);
    
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void keyReleaseEvent(QKeyEvent *event) override;
    
    virtual void update(float dt) override;
    
private:
    bool wPressed_ = false;
    bool aPressed_ = false;
    bool sPressed_ = false;
    bool dPressed_ = false;
    bool rbuttonDown_ = false;
    QPoint oldMousePos_;
    float speed_ = 10.f;
};

#endif // FPSCAMERACONTROLLER_H
