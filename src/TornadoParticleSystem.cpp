#include "TornadoParticleSystem.h"
#include "common.h"

#define NUM_PARTICLES 80
// This also, by necessity, determines particle spawn rate (along with height)!
#define PARTICLE_CYCLE_SPEED 20.0
#define TORNADO_MIN_OPACITY 0.2
#define TORNADO_MAX_OPACITY 1.0
#define TORNADO_MIN_COLOR 0.4
#define TORNADO_MAX_COLOR 0.5

TornadoParticleSystem::TornadoParticleSystem()
{

}

TornadoParticleSystem::TornadoParticleSystem(Tornado* tornado)
{
    m_tornado = tornado;
    if(!m_cycleSpeed)
        m_cycleSpeed = PARTICLE_CYCLE_SPEED;
    if(!m_numParticles)
        m_numParticles = NUM_PARTICLES;
    // Set up and push back all particles we want to use.
    //init();
}

void TornadoParticleSystem::init()
{
    setEmissionRate((int)((m_numParticles * abs(m_cycleSpeed)) / m_tornado->getHeight() * 0.9));
    setMaxParticleCount(m_numParticles);
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
    if(m_useOpacity){
        particle->opacity = TORNADO_MIN_OPACITY;
    }
    float randC = randf(TORNADO_MIN_COLOR, TORNADO_MAX_COLOR);
    particle->color = {randC, randC, randC};
}

void TornadoParticleSystem::updateParticle(Particle &particle, float dt)
{
    float lprop = particle.life / particle.maxLife;
    float sterm = 1.5 - (4.0/3.0 * lprop);
    if(lprop >= 0.75){
        sterm = 0.5 + (4.0 * (lprop - 0.75));
    }

    particle.position.setY(particle.position.y() - (m_cycleSpeed * dt * sterm));
    particle.position = getParticlePosition(&particle, particle.position.y());
    particle.size = getParticleSize(particle.position.y());
    particle.rotation = updateParticleRotation(&particle, dt);
    if(m_useOpacity){
        float oprop = sqrt(lprop);
        particle.opacity = (oprop * TORNADO_MAX_OPACITY) + (TORNADO_MIN_OPACITY * (1.0 - oprop));
    }
    else if(m_randOpacity){
        float oprop = randf(0.3, 0.6);
        particle.opacity = oprop;
    }
    float randC = min((float)TORNADO_MAX_COLOR, max((float)TORNADO_MIN_COLOR, (float) particle.color.x() + randf(-0.02, 0.02)));
    particle.color = {randC, randC, randC};
}

vec3 TornadoParticleSystem::getParticlePosition(Particle *p, float yval)
{
    return m_tornado->interpLocal(yval);
}

float TornadoParticleSystem::getParticleSize(float yval)
{
    return m_tornado->interpWidth(yval);
}

float TornadoParticleSystem::updateParticleRotation(Particle* p, float dt)
{
    float rot = p->rotation;
    float hprop = (p->position.y() - m_tornado->getOrigin().y()) / m_tornado->getHeight();
    float rotFactor = (1.0 + hprop) * dt * randf(20.0, 25.0);
    return rot + rotFactor;
}

