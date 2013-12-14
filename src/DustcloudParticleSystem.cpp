#include "DustcloudParticleSystem.h"

#define NUM_PARTICLES_DUST 75
#define DUST_CYCLE_SPEED -15.0
#define DUST_ROT_SPEED -6.0

DustcloudParticleSystem::DustcloudParticleSystem(Tornado* tornado)
{
    m_tornado = tornado;
    // Nothing that TornadoParticleSystem doesn't do...
}

void DustcloudParticleSystem::init()
{
    m_cycleSpeed = DUST_CYCLE_SPEED;
    m_numParticles = NUM_PARTICLES_DUST;
    m_useOpacity = false;
    m_randOpacity = true;
    this->TornadoParticleSystem::init();
}

DustcloudParticleSystem::~DustcloudParticleSystem()
{
    // Nothing to see here...
}

void DustcloudParticleSystem::spawnParticle(Particle *particle)
{
    particle->position.setY(0.0);
    particle->maxLife = m_tornado->getHeight() / abs(m_cycleSpeed);
    particle->rotation = 2.0 * M_PI * (double)rand() / RAND_MAX;
}

vec3 DustcloudParticleSystem::getParticlePosition(Particle *p, float yval)
{
    // Hacky but simple and effective way of making dust swirl: use rotation as angle around spine!
    vec3 rv = m_tornado->interpLocal(yval); // Get spine position first.
    float revPoint = 0.3;
    float adjHeight = (m_tornado->getHeight() * revPoint) + abs(yval - (m_tornado->getHeight() * revPoint));
    float width = 1.2 * m_tornado->interpWidth(adjHeight);
    rv.setX(rv.x() + (width * sin(p->rotation)));
    rv.setZ(rv.z() + (width * cos(p->rotation)));
    return rv;
}

float DustcloudParticleSystem::getParticleSize(float yval)
{
    return 5.0;//m_tornado->interpWidth(yval);
}

float DustcloudParticleSystem::updateParticleRotation(float rot, float dt)
{
    return rot + (DUST_ROT_SPEED * dt);
}

