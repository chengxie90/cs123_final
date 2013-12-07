#ifndef COMMON_H
#define COMMON_H

#include <stdlib.h>
#include <stdio.h>
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <map>
using std::map;
#include <assert.h>
#include <memory>
using std::shared_ptr;
using std::unique_ptr;
#include <algorithm>
using std::min;
using std::max;
using std::sort;
#include <iostream>
using std::cout;
using std::endl;
//#include <QColor>
//typedef QColor Color;
#include <QVector3D>
typedef QVector3D Color;


#ifdef QT_DEBUG
    #define DEBUG_LOG(message) printf("-->");printf(message);printf("\n");fflush(stdout);
#else
    #define DEBUG_LOG(message)
#endif

class DrawContext;
class Light;
class Camera;
class SceneObject;
class Scene;
class CameraController;
class Texture;
class MeshRenderer;

inline float randf() {
    return (float)rand() / RAND_MAX * 2 - 1;
}

#endif // COMMON_H
