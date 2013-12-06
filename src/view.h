#ifndef VIEW_H
#define VIEW_H

#include <QTime>
#include <QTimer>
#include <QGLWidget>
#include <QPoint>
#include "common.h"

class View : public QGLWidget
{
    Q_OBJECT

public:
    View(QWidget *parent);
    ~View();
    
private slots:
    void tick();
    
private:
    virtual void initializeGL() override;
    virtual void paintGL() override;
    virtual void resizeGL(int w, int h) override;

    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void wheelEvent(QWheelEvent *event) override;

    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void keyReleaseEvent(QKeyEvent *event) override;

    QTime time_;
    QTimer timer_;
    
    Camera* camera_ = NULL;
    CameraController* cameraController_ = NULL;
    Scene* scene_ = NULL;
    
};

#endif // VIEW_H

