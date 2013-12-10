#ifndef TORNADO_H
#define TORNADO_H

#define NUM_CONTROL_POINTS 9

#include "common.h"
#include "sceneobject.h"

class Tornado : public SceneObject
{
public:
    Tornado();
    Tornado(vec3 startOrigin);
    virtual ~Tornado();
    float getHeight(){return m_height;} // Allow access to height and age.
    float getAge(){return m_age;}
    vec3 getOrigin(){return m_origin;}  // Fetch the origin and control points for the tornado.
    vec3* getControlPoints(){return m_controlPoints;}
    vec3 interp(float height);          // Get the location of the tornado spine at y-value height.
    vec3 interpLocal(float height);     // Same as interp, but in relation to the tornado's base.
    float interpWidth(float height);    // Get the tornado width at a given local height...

protected:
    float m_height;
    float m_age;            // How long has this tornado been active? Useful if we want to descend from the sky.
    vec3 m_origin;          // The point where the tornado hits the terrain height map.
    vec3* m_controlPoints;  // An array of the control points needed for the tornado - these are offsets from origin!
    float* m_controlWidths; // The width of the tornado at each step!
    virtual void init();    // Part of both constructors.
};

#endif // TORNADO_H
