#include "SplashParticleSystem.h"

#define NUM_PARTICLES_SPLASH 40
#define SPLASH_CYCLE_SPEED -15.0
#define SPLASH_ROT_SPEED -6.0

SplashParticleSystem::SplashParticleSystem(Tornado* tornado)
{
    m_tornado = tornado;
    // Nothing that TornadoParticleSystem doesn't do...
}

void SplashParticleSystem::init()
{
    m_cycleSpeed = SPLASH_CYCLE_SPEED;
    m_numParticles = NUM_PARTICLES_SPLASH;
    m_useOpacity = false;
    m_randOpacity = true;
    this->TornadoParticleSystem::init();
    setEmissionRate((int)((m_numParticles * abs(m_cycleSpeed)) / m_tornado->getHeight() * 0.25));
}

SplashParticleSystem::~SplashParticleSystem()
{
    // Nothing to see here...
}

void SplashParticleSystem::spawnParticle(Particle *particle)
{
    particle->position.setY(0.0);
    particle->maxLife = m_tornado->getHeight() / abs(m_cycleSpeed) * 0.3;
    particle->rotation = 2.0 * M_PI * (double)rand() / RAND_MAX;
}

vec3 SplashParticleSystem::getParticlePosition(Particle *p, float yval)
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

float SplashParticleSystem::getParticleSize(float yval)
{
    return 1.1 * m_tornado->interpWidth(yval);
}

float SplashParticleSystem::updateParticleRotation(float rot, float dt)
{
    return rot + (SPLASH_ROT_SPEED * dt);
}
