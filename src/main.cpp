#include <QApplication>
#include <QGLFormat>
#include "mainwindow.h"
#include "view.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    QGLFormat glFormat;
    glFormat.setVersion(3, 3);
    
    glFormat.setProfile(QGLFormat::CoreProfile);
    //glFormat.setProfile(QGLFormat::CompatibilityProfile);
    
    glFormat.setSampleBuffers( true );
    glFormat.setSamples(8);
    
    QGLFormat::setDefaultFormat(glFormat);
    
    MainWindow w;

    bool startFullscreen = false;

    w.show();

    if (startFullscreen) {
        // We cannot use w.showFullscreen() here because on Linux that creates the
        // window behind all other windows, so we have to set it to fullscreen after
        // it has been shown.
        w.setWindowState(w.windowState() | Qt::WindowFullScreen);
    }

    return a.exec();
}

