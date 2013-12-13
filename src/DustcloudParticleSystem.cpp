#include "DustcloudParticleSystem.h"

#define NUM_PARTICLES_DUST 80
#define DUST_CYCLE_SPEED 20.0
#define DUST_ROT_SPEED 1.5

DustcloudParticleSystem::DustcloudParticleSystem(Tornado* tornado)
{
    m_tornado = tornado;
    m_cycleSpeed = DUST_CYCLE_SPEED;
    m_numParticles = NUM_PARTICLES_DUST;
    // Set up and push back all particles we want to use.
    init();
}

void DustcloudParticleSystem::init()
{
    mesh_ = new Mesh();
    m_active_count = 0;
    m_lastActivation = 0.0;
    // "Template" particle, modify and push back into the vector to create copies of it.
    Particle p;
    p.active = false;
    p.size = 0.0;
    p.position.setY(-1.0);
    for(int it = m_numParticles - 1; it >= 0; it--){
        // Uncomment this if we don't want the particles to grow down.
        /*float heightScale = pow((float)it/(NUM_PARTICLES - 1), 2.0);
        float curHeight = m_tornado->getHeight() * heightScale;
        p.position = m_tornado->interpLocal(curHeight);
        p.size = m_tornado->interpWidth(curHeight);
        p.active = true;*/
        particles_.push_back(p);
    }
}

DustcloudParticleSystem::~DustcloudParticleSystem()
{
    // Nothing to see here...
}

vec3 DustcloudParticleSystem::getParticlePosition(float yval)
{
    return m_tornado->interpLocal(yval);
}

float DustcloudParticleSystem::getParticleSize(float yval)
{
    return m_tornado->interpWidth(yval);
}
