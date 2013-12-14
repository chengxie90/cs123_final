QT += core gui opengl

LIBS += -L"$$_PRO_FILE_PWD_/glew/lib" -lGLEW 

CONFIG += c++11

unix:!macx {
    QMAKE_CXXFLAGS += -std=c++11
}

TARGET = final
TEMPLATE = app

# If you add your own folders, add them to INCLUDEPATH and DEPENDPATH, e.g.

CONFIG -= depend_includepath

INCLUDEPATH += "glew/include"

SOURCES += main.cpp \
    mainwindow.cpp \
    view.cpp \
    scene.cpp \
    camera.cpp \
    mesh.cpp \
    sceneobject.cpp \
    geometry.cpp \
    pointlight.cpp \
    directlight.cpp \
    cameracontroller.cpp \
    meshcache.cpp \
    texturecache.cpp \
    texture.cpp \
    shadercache.cpp \
    particlesystem.cpp \
    phongmaterial.cpp \
    particlematerial.cpp \
    skybox.cpp \
    skyboxmaterial.cpp \
    texture2d.cpp \
    texturecube.cpp \
    terrain.cpp \
    meshutility.cpp \
    orbitcameracontroller.cpp \
    fpscameracontroller.cpp \
    Tornado.cpp \
    TornadoParticleSystem.cpp \
    DustcloudParticleSystem.cpp \
    terrainmaterial.cpp \
    material.cpp \
    cloud.cpp \
    rain.cpp \
    rainsplash.cpp \
    PhysicsObject.cpp \
    SplashParticleSystem.cpp \
    wind.cpp

HEADERS += mainwindow.h \
    view.h \
    geometry.h \
    common.h \
    scene.h \
    camera.h \
    light.h \
    mesh.h \
    material.h \
    sceneobject.h \
    drawcontext.h \
    pointlight.h \
    directlight.h \
    cameracontroller.h \
    resourcecache.h \
    meshcache.h \
    texturecache.h \
    texture.h \
    shadercache.h \
    particlesystem.h \
    phongmaterial.h \
    particlematerial.h \
    shader.h \
    skybox.h \
    skyboxmaterial.h \
    texture2d.h \
    texturecube.h \
    terrain.h \
    meshutility.h \
    orbitcameracontroller.h \
    fpscameracontroller.h \
    Tornado.h \
    TornadoParticleSystem.h \
    DustcloudParticleSystem.h \
    terrainmaterial.h \
    cloud.h \
    rain.h \
    rainsplash.h \
    PhysicsObject.h \
    SplashParticleSystem.h \
    wind.h

FORMS += mainwindow.ui
