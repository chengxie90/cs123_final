#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "common.h"
#include <QVector2D>
#include <QVector3D>
#include <QVector4D>
#include <QMatrix4x4>

//using glm::vec2;
//using glm::vec3;
//using glm::vec4;
//using glm::mat4x4;

typedef QVector2D vec2;
typedef QVector3D vec3;
typedef QVector4D vec4;
typedef QMatrix4x4 mat4;

using std::ostream;

inline ostream& operator<<(ostream& os, const vec3& vec) {
    os << vec.x() << " " << vec.y() << " " << vec.z();
    return os;
}

//class Transform {
//public:
//    mat4& matrix();
//    const mat4& matrix() const;
//    void setMatrix(const mat4 &matrix);
    
//    vec3 position() const;
//    void setPosition(const vec3& position);
    
//    void translate(const vec3& trans);
    
//private:
//    mat4 matrix_;
//};


#endif // GEOMETRY_H
