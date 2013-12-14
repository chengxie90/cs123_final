#include <GL/glew.h>
#include "view.h"
#include <QApplication>
#include <QKeyEvent>
#include "camera.h"
#include "scene.h"
#include "drawcontext.h"
#include "orbitcameracontroller.h"
#include "fpscameracontroller.h"
#include <QSound>

using namespace std;

View::View(QWidget *parent) : QGLWidget(parent)
{   
    // View needs all mouse move events, not just mouse drag events
    setMouseTracking(true);

    // Hide the cursor since this is a fullscreen app
    //setCursor(Qt::BlankCursor);

    // View needs keyboard focus
    setFocusPolicy(Qt::StrongFocus);

    // The game loop is implemented using a timer
    connect(&timer_, SIGNAL(timeout()), this, SLOT(tick()));
}

View::~View()
{
    delete scene_;
    delete camera_;
}

void View::initializeGL()
{       
    time_.start();
    timer_.start(1000 / 60);

    glewExperimental = GL_TRUE; 
    GLenum err = glewInit();
    
    if( GLEW_OK != err )
    {
        fprintf(stderr, "Error initializing GLEW: %s\n",
                        glewGetErrorString(err) );
    }
    
    glClearColor(1, 0.7, 0, 1.0);
    glClearDepth(1.0);
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);    
    
    glFrontFace(GL_CCW);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    QCursor::setPos(mapToGlobal(QPoint(width() / 2, height() / 2)));
    
    camera_ = new Camera();
    //cameraController_ = new OrbitCameraController(camera_);
    cameraController_ = new FPSCameraController(camera_);
    
    scene_ = new Scene();

    //QSound *sound = new QSound("sounds/background.wav");
    //sound->setLoops(100);
    //sound->play();
}

void View::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    float seconds = time_.restart() * 0.001f;
    
    cameraController_->update(seconds);
    
    DrawContext context;
    context.deltaTime = seconds;
    context.camera = camera_;
    
    scene_->render(context);
}

void View::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    float aspectRatio = (float)w / h;
    camera_->setAspectRatio(aspectRatio);
}

void View::mousePressEvent(QMouseEvent *event)
{
    cameraController_->mousePressEvent(event);
    
    if (event->button() == Qt::LeftButton) {
        QPoint screenPoint = event->pos();
        //cout << screenPoint.x() << " " << screenPoint.y() << endl;
        
        float screenX = screenPoint.x();
        float screenY = height() - screenPoint.y();
        float x = screenX / width() * 2 - 1;
        float y = screenY / height() * 2 - 1;
        float z;
        glReadPixels(screenX, screenY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
        
        vec4 p = {x, y, 0, 1};
        
        p = camera_->transform() * camera_->projectionMatrix().inverted() * p;
        
        p = p / p.w();
        
        vec3 camPos = camera_->position();
        
        vec3 dir = p.toVector3D() - camPos;
        dir.normalize();
        
        float t = (0 - camPos.y()) / dir.y();
        
        vec3 hit = camPos + t * dir;
        
        //cout << hit << endl;
        if(m_keyDown){
            scene_->placeObject(hit);
        }
        else{
            scene_->pick(hit);
        }
    }
    
    update();
}

void View::mouseMoveEvent(QMouseEvent *event)
{
    cameraController_->mouseMoveEvent(event);
    update();
}

void View::mouseReleaseEvent(QMouseEvent *event)
{
    cameraController_->mouseReleaseEvent(event);
    update();
}

void View::wheelEvent(QWheelEvent *event)
{
    cameraController_->wheelEvent(event);
}

void View::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) QApplication::quit();
    if(event->key() == Qt::Key_Space){
        m_keyDown = true;
    }
    cameraController_->keyPressEvent(event);
    update();
}

void View::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space){
        m_keyDown = false;
    }
    cameraController_->keyReleaseEvent(event);
    update();
}

void View::tick()
{
    // Flag this view for repainting (Qt will call paintGL() soon after)
    update();
}
