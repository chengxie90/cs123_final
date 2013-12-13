#include "DustcloudParticleSystem.h"

#define NUM_PARTICLES_DUST 180
#define DUST_CYCLE_SPEED -15.0
#define DUST_ROT_SPEED 10.0

DustcloudParticleSystem::DustcloudParticleSystem(Tornado* tornado)
{
    m_tornado = tornado;
    // Nothing that TornadoParticleSystem doesn't do...
}

void DustcloudParticleSystem::init()
{
    if(!m_cycleSpeed){
        m_cycleSpeed = DUST_CYCLE_SPEED;
    }
    if(!m_numParticles){
        m_numParticles = NUM_PARTICLES_DUST;
    }
    m_active_count = 0;
    m_lastActivation = 0.0;
    // "Template" particle, modify and push back into the vector to create copies of it.
    Particle p;
    p.active = false;
    p.size = 0.0;
    p.position.setY(-1.0);
    for(int it = 0; it < m_numParticles; it++){
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

vec3 DustcloudParticleSystem::getParticlePosition(Particle *p, float yval)
{
    // Hacky but simple and effective way of making dust swirl: use rotation as angle around spine!
    vec3 rv = m_tornado->interpLocal(yval); // Get spine position first.
    float adjHeight = (m_tornado->getHeight()/2.0) + abs(yval - (m_tornado->getHeight()/2.0));
    float width = 1.2 * m_tornado->interpWidth(adjHeight);
    rv.setX(rv.x() + (width * sin(p->rotation)));
    rv.setZ(rv.z() + (width * cos(p->rotation)));
    return rv;
}

float DustcloudParticleSystem::getParticleSize(float yval)
{
    return 3.0;//m_tornado->interpWidth(yval);
}

float DustcloudParticleSystem::updateParticleRotation(float rot, float dt)
{
    return rot + (DUST_ROT_SPEED * dt);
}

bool DustcloudParticleSystem::resetThreshold(Particle* p)
{
    float yval = p->position.y();
    float threshold = m_tornado->getHeight() - (3.0 * m_tornado->getHeight() / m_numParticles);
    return yval > threshold;
}

void DustcloudParticleSystem::resetParticle(Particle* p)
{
    p->position.setY(0.0);
    // This particle is always the first one!
    particles_.push_back(*p);
    particles_.erase(particles_.begin());
    std::cout<<"ASDJHAKWDJ"<<endl;
}

