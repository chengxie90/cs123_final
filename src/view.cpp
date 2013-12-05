#include <GL/glew.h>
#include "view.h"
#include <QApplication>
#include <QKeyEvent>
#include <QGLShader>
#include <QGLShaderProgram>
#include <geometry.h>
#include "mesh.h"
#include "common.h"
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
    assert(sizeof(qreal) == sizeof(float));
    
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
    
    QGLShaderProgram program;
    program.addShaderFromSourceFile(QGLShader::Vertex, "shaders/basic.vs");
    program.addShaderFromSourceFile(QGLShader::Fragment, "shaders/basic.fs");
    program.link();
    
    cout << program.log().toStdString() << endl;
    
    program.bind();
    
    VertexBuffer vb;
    Vertex v1, v2, v3;
    v1.position = vec3{-0.5, -0.5, 0};
    v2.position = vec3{0.5, -0.5, 0};
    v3.position = vec3{0, 0.5, 0};
    vb.push_back(v1);
    vb.push_back(v2);
    vb.push_back(v3);
    
    IndexBuffer ib;
    ib.push_back(0);
    ib.push_back(1);
    ib.push_back(2);
    
    mesh.setVertexBuffer(std::move(vb));
    mesh.setIndexBuffer(std::move(ib));
    
    program.setUniformValue("view", camera.getViewMatrix());
    program.setUniformValue("projection", camera.getProjectionMatrix());
}

void View::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    mesh.render();
}

void View::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void View::mousePressEvent(QMouseEvent *event)
{
}

void View::mouseMoveEvent(QMouseEvent *event)
{
//    int deltaX = event->x() - width() / 2;
//    int deltaY = event->y() - height() / 2;
    
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
