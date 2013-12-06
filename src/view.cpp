#include <GL/glew.h>
#include "view.h"
#include <QApplication>
#include <QKeyEvent>
#include "geometry.h"
#include "mesh.h"
#include "common.h"
#include "camera.h"
#include "material.h"
#include "directlight.h"
using namespace std;

View::View(QWidget *parent) : QGLWidget(parent)
{   
    // View needs all mouse move events, not just mouse drag events
    setMouseTracking(true);

    // Hide the cursor since this is a fullscreen app
    setCursor(Qt::BlankCursor);

    // View needs keyboard focus
    setFocusPolicy(Qt::StrongFocus);

    // The game loop is implemented using a timer
    connect(&timer, SIGNAL(timeout()), this, SLOT(tick()));
}

View::~View()
{
    
}

void View::initializeGL()
{   
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    time.start();
    timer.start(1000 / 60);

    glewExperimental = GL_TRUE; 
    GLenum err = glewInit();
    
    if( GLEW_OK != err )
    {
        fprintf(stderr, "Error initializing GLEW: %s\n",
                        glewGetErrorString(err) );
    }
    
    cout << glGetString(GL_VERSION) << endl;
    
    glClearColor(1, 0.7, 0, 1.0);
    glClearDepth(1.0);
    
    camera = new Camera();
    Material* material = new Material("basic");
    material->setAmbient({0.3, 0.3, 0.3, 1.0});
    material->setDiffuse({0.7, 0.7, 0.7, 1.0});
    DirectLight* light = new DirectLight({-1, -0.5, -1}, {1.0, 1.0, 1.0, 1.0});
    
    mesh.setMaterial(material);
    
    context.camera = camera;
    context.light = light;
    
    mesh.load("models/sphere.obj");
    
    QCursor::setPos(mapToGlobal(QPoint(width() / 2, height() / 2)));
}

void View::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    mesh.render(context);
}

void View::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    float aspectRatio = (float)w / h;
    camera->setAspectRatio(aspectRatio);
}

void View::mousePressEvent(QMouseEvent *event)
{
    int deltaX = event->x();
    int deltaY = event->y();
    
    printf("%d %d\n", deltaX, deltaY);
    fflush(stdout);
}

void View::mouseMoveEvent(QMouseEvent *event)
{
//    int deltaX = event->x();// - width() / 2;
//    int deltaY = event->y();// - height() / 2;
    
//    cout << deltaX << " " << deltaY << endl;
//    fflush(stdout);
//    if (!deltaX && !deltaY) return;

    // TODO: Handle mouse movements here
}

void View::mouseReleaseEvent(QMouseEvent *event)
{
}

void View::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) QApplication::quit();

    // TODO: Handle keyboard presses here
}

void View::keyReleaseEvent(QKeyEvent *event)
{
    
}

void View::tick()
{
    // Get the number of seconds since the last tick (variable update rate)
    float seconds = time.restart() * 0.001f;

    // TODO: Implement the demo update here

    // Flag this view for repainting (Qt will call paintGL() soon after)
    update();
}
