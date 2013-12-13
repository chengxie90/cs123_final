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
    m_cycleSpeed = PARTICLE_CYCLE_SPEED;
    m_numParticles = NUM_PARTICLES;
    // Set up and push back all particles we want to use.
    init();
}

void TornadoParticleSystem::init()
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
    // Only activate more paticles if we don't have enough already.
    bool activated = !(m_active_count < m_numParticles);
    for (Particle& particle : particles_) {
        if(particle.active){
            particle.position.setY(particle.position.y() - (m_cycleSpeed * dt));
            // If the particle is going into the ground, reset it.
            // Keep a buffer of 5 thresholds to prevent breaks in the tornado effect.
            if(resetThreshold(&particle)){
                resetParticle(&particle);
            }
            particle.position = getParticlePosition(particle.position.y());
            particle.size = getParticleSize(particle.position.y());
            particle.rotation += 90 * dt;
        }
        else if(!activated){
            activated = true;
            // If we are past the threshold, it's time to bring a new pixel online,
            float threshold = m_tornado->getHeight() / (m_cycleSpeed * m_numParticles);
            if(m_lastActivation >= threshold){
                std::cout<<"PING"<<endl;
                m_lastActivation -= threshold;
                particle.active = true;
                m_active_count++;
                // particle.position's y-value is less than 0, so it will be reset next update.
            }
        }
    }
}

vec3 TornadoParticleSystem::getParticlePosition(float yval)
{
    return m_tornado->interpLocal(yval);
}

float TornadoParticleSystem::getParticleSize(float yval)
{
    return m_tornado->interpWidth(yval);
}

bool TornadoParticleSystem::resetThreshold(Particle* p)
{
    float yval = p->position.y();
    float threshold = 5.0 * m_tornado->getHeight() / m_numParticles;
    return yval < threshold;
}

void TornadoParticleSystem::resetParticle(Particle* p)
{
    p->position.setY(m_tornado->getHeight());
}

