#include "TornadoParticleSystem.h"

#define NUM_PARTICLES 60
// This also, by necessity, determines particle spawn rate (along with height)!
#define PARTICLE_CYCLE_SPEED 20.0

TornadoParticleSystem::TornadoParticleSystem()
{
    m_cycleSpeed = PARTICLE_CYCLE_SPEED;
    m_numParticles = NUM_PARTICLES;
    // Set up and push back all particles we want to use.
    init();
}

TornadoParticleSystem::TornadoParticleSystem(Tornado* tornado)
{
    m_tornado = tornado;
    if(!m_cycleSpeed)
        m_cycleSpeed = PARTICLE_CYCLE_SPEED;
    if(!m_numParticles)
        m_numParticles = NUM_PARTICLES;
    // Set up and push back all particles we want to use.
    init();
}

void TornadoParticleSystem::init()
{
    setEmissionRate((int)((m_numParticles * m_cycleSpeed) / m_tornado->getHeight()));
    setMaxParticleCount(m_numParticles);
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

TornadoParticleSystem::~TornadoParticleSystem()
{
    // Free the memory associated with particles_ by swapping with an empty vector.
    // vector<Particle>().swap(particles_);
}

void TornadoParticleSystem::update(float dt)
{
    m_lastActivation += dt;
    m_tornado->update(dt);
    // Update our transform to match the new origin.
    transform_.setToIdentity();
    transform_.translate(m_tornado->getOrigin());
    this->ParticleSystem::update(dt);
}

void TornadoParticleSystem::spawnParticle(Particle *particle)
{
    particle->position.setY(m_tornado->getHeight());
    particle->maxLife = m_tornado->getHeight() / m_cycleSpeed;
}

void TornadoParticleSystem::updateParticle(Particle &particle, float dt)
{
    particle.position.setY(particle.position.y() - (m_cycleSpeed * dt));
    particle.position = getParticlePosition(&particle, particle.position.y());
    particle.size = getParticleSize(particle.position.y());
    particle.rotation = updateParticleRotation(particle.rotation, dt);
}

vec3 TornadoParticleSystem::getParticlePosition(Particle *p, float yval)
{
    return m_tornado->interpLocal(yval);
}

float TornadoParticleSystem::getParticleSize(float yval)
{
    return m_tornado->interpWidth(yval);
}

float TornadoParticleSystem::updateParticleRotation(float rot, float dt)
{
    return rot + (90.0 * dt);
}

