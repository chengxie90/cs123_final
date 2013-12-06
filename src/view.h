#ifndef VIEW_H
#define VIEW_H

#include <QTime>
#include <QTimer>
#include <QGLWidget>
#include "common.h"

class View : public QGLWidget
{
    Q_OBJECT

public:
    View(QWidget *parent);
    ~View();

private:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    QTime time_;
    QTimer timer_;
    
    Camera* camera_ = NULL;
    Scene* scene_ = NULL;
    
private slots:
    void tick();
};

#endif // VIEW_H

