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
# DEPENDPATH += folder1 folder2

SOURCES += main.cpp \
    mainwindow.cpp \
    view.cpp

HEADERS += mainwindow.h \
    view.h \
    geometry.h \
    common.h

FORMS += mainwindow.ui
