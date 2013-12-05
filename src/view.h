#ifndef VIEW_H
#define VIEW_H

#include <QTime>
#include <QTimer>
#include <QGLWidget>
#include "mesh.h"
#include "camera.h"

class View : public QGLWidget
{
    Q_OBJECT

public:
    View(QWidget *parent);
    ~View();

private:
    QTime time;
    QTimer timer;

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    Mesh mesh;
    Camera camera;
private slots:
    void tick();
};

#endif // VIEW_H

