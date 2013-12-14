#include "Tornado.h"

#define TORNADO_INIT_HEIGHT 90.0
#define TORNADO_INIT_SPEED 2.0
#define TORNADO_SCALE_FACTOR 35.0
#define TORNADO_SUB_GROUND 10.0

Tornado::Tornado(){
    // Just initialize with default values.
    m_origin = vec3(0.0, 0.0, 0.0);
    init();
}

Tornado::Tornado(vec3 startOrigin, Terrain* terr)
{
    // Add origin, then initialize.
    m_terrain = terr;
    m_origin = startOrigin;
    init();
}

void Tornado::init()
{
    // Initialize height and age...
    m_height = TORNADO_INIT_HEIGHT;
    m_age = 0.0;
    m_speed = TORNADO_INIT_SPEED;
    // Don't go anywhere until setDestination is a thing.
    m_destination = m_origin;
    // Initialize an array of control points and widths...
    m_controlPoints = new vec3[NUM_CONTROL_POINTS];
    m_controlWidths = new float[NUM_CONTROL_POINTS];
    m_initWidths = new float[NUM_CONTROL_POINTS];
    float segmentSize = m_height/(NUM_CONTROL_POINTS - 1);
    for(int it = 0; it < NUM_CONTROL_POINTS; it++){
        float th = it * segmentSize;
        m_controlPoints[it].setX(0.0);
        m_controlPoints[it].setZ(0.0);
        m_controlPoints[it].setY(th);
        // width should be a function of height.
        // Should edit scale factor to match texture?
        m_initWidths[it] = initWidth(th);
        m_controlWidths[it] = m_initWidths[it];
    }
}

Tornado::~Tornado()
{
    delete[] m_controlPoints;
    delete[] m_controlWidths;
    delete[] m_initWidths;
}

// Interpolate the tornado's spine position at a given world-space height.
vec3 Tornado::interp(float height)
{
    return interpLocal(height - m_origin.y());
}

// Interpolate the tornado's local spine position at a some height in the tornado.
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
    rv.setX(p1.x() * (1.0 - offset) + (p2.x() * offset));
    rv.setZ(p1.z() * (1.0 - offset) + (p2.z() * offset));
    rv.setY(height);
    return rv;
}

// Interpolate to find the tornado width at some local height.
float Tornado::interpWidth(float height)
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
    float w1 = m_controlWidths[ind];
    float w2 = m_controlWidths[ind + 1];
    // Right now, this is just linear interpolation. If we want, we can bring in a bezier curve or something.
    float rv = (w1 * (1.0 - offset)) + (w2 * offset);
    return rv;
}

// Interpolate to find the tornado width at some local height.
float Tornado::initWidth(float height)
{
    float wp = abs(height)/m_height;
    if (wp < 0.25)
        wp = 0.5 - wp;
    float rv =  pow(wp, 2.0) * TORNADO_SCALE_FACTOR;
    return rv;
}

#define TORNADO_RAND_SCALE 10.0
#define TORNADO_MAX_TWIST 0.10
#define TORNADO_MAX_DELTA 0.20

void Tornado::update(float dt)
{
    vec3 diff = m_destination - m_origin;
    diff.setY(0.0);
    float dist = min((double) diff.length(), (double) m_speed * dt);
    diff.normalize();
    m_origin += (diff * dist);
    // Set the origin's y-value to sub_ground below the height map at the current point.
    float terrainHeight = m_terrain->height(m_origin.x(), m_origin.y());
    // std::cout<<terrainHeight<<endl;
    m_origin.setY(terrainHeight - TORNADO_SUB_GROUND);
    // Add a little random shake to the control points...
    for(int it = 0; it < NUM_CONTROL_POINTS; it++){
        // Shake control point position...
        vec3 rvec;
        double hprop = (double)it / (double)(NUM_CONTROL_POINTS - 1);
        double rx = dt * hprop * TORNADO_RAND_SCALE * randf(-1.0, 1.0);
        double ry = dt * hprop * TORNADO_RAND_SCALE * randf(-1.0, 1.0);
        rvec.setX(min(TORNADO_MAX_TWIST, max(-TORNADO_MAX_TWIST, rx)));
        rvec.setZ(min(TORNADO_MAX_TWIST, max(-TORNADO_MAX_TWIST, ry)));
        rvec.setY(0.0);
        // Shake control point widths...
        float rwf = dt * hprop * TORNADO_RAND_SCALE * 0.5;
        m_controlWidths[it] *= randf(1.0 - rwf, 1.0 + rwf);
        m_controlPoints[it] += rvec;
    }
    capControls();
}

void Tornado::capControls()
{
    for(int it = 0; it < NUM_CONTROL_POINTS; it++){
        double hprop = (double)it / (double)(NUM_CONTROL_POINTS - 1);
        double maxDelta = TORNADO_MAX_DELTA * hprop;
        double maxDT = maxDelta * 20.0;
        // Cap control point x and z...
        m_controlPoints[it].setX(min((float)maxDT, max(-(float)maxDT, m_controlPoints[it].x())));
        m_controlPoints[it].setZ(min((float)maxDT, max(-(float)maxDT, m_controlPoints[it].z())));
        // Cap control width...
        float minW = (1.0 - maxDelta) * m_initWidths[it];
        float maxW = (1.0 + maxDelta) * m_initWidths[it];
        m_controlWidths[it] = min(maxW, max(minW, m_controlWidths[it]));
    }
}
