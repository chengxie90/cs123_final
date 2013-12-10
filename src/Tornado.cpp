#include "Tornado.h"

#define TORNADO_INIT_HEIGHT 120.0
#define TORNADO_SCALE_FACTOR 45.0

Tornado::Tornado(){
    // Just initialize with default values.
    init();
}

Tornado::Tornado(vec3 startOrigin)
{
    // Initialize, then add origin.
    init();
    m_origin = startOrigin;
}

void Tornado::init()
{
    // Initialize height and age...
    m_height = TORNADO_INIT_HEIGHT;
    m_age = 0.0;
    // Initialize an array of control points and widths...
    m_controlPoints = new vec3[NUM_CONTROL_POINTS];
    m_controlWidths = new float[NUM_CONTROL_POINTS];
    float segmentSize = m_height/(NUM_CONTROL_POINTS - 1);
    for(int it = 0; it < NUM_CONTROL_POINTS; it++){
        float th = it * segmentSize;
        m_controlPoints[it].setX(0.0);
        m_controlPoints[it].setZ(0.0);
        m_controlPoints[it].setY(th);
        // width should be a function of height.
        // Should edit scale factor to match texture?
        m_controlWidths[it] = interpWidth(th);
    }
    m_origin = vec3(0.0, 0.0, 0.0);
}

Tornado::~Tornado()
{
    delete[] m_controlPoints;
    delete[] m_controlWidths;
}

// Interpolate the tornado's spine position at a given world-space height.
vec3 Tornado::interp(float height)
{
    return interpLocal(height - m_origin.y());
}

// Interpolate the tornado's spine position at a some height in the tornado.
vec3 Tornado::interpLocal(float height)
{
    float segmentSize = m_height/(NUM_CONTROL_POINTS - 1);
    int ind = height / segmentSize;
    float offset = height - (float) (segmentSize * ind);
    offset /= segmentSize;
    if(height >= m_height){
        ind = NUM_CONTROL_POINTS - 2;
        offset = 1.0;
    }
    else if(height <= 0.0){
        ind = 0;
        offset = 0.0;
    }
    vec3 p1 = m_controlPoints[ind];
    vec3 p2 = m_controlPoints[ind + 1];
    vec3 rv;
    // Right now, this is just linear interpolation. If we want, we can bring in a bezier curve or something.
    rv.setX((p1.x() * (1.0 - offset)) + (p2.x() * offset));
    rv.setZ((p1.z() * (1.0 - offset)) + (p2.z() * offset));
    rv.setY(m_origin.y() + height);
    return rv;
}

// Interpolate to find the tornado width at some local height.
float Tornado::interpWidth(float height)
{
    float wp = abs(height)/m_height;
    if (wp < 0.225)
        wp = 0.45 - wp;
    float rv =  pow(wp, 2.0) * TORNADO_SCALE_FACTOR;
    return rv;
}
