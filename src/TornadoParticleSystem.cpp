#include "TornadoParticleSystem.h"

#define NUM_PARTICLES 60

TornadoParticleSystem::TornadoParticleSystem(Tornado* tornado)
{
    m_tornado = tornado;
    // Set up and push back all particles we want to use.
    init();
}

void TornadoParticleSystem::init()
{
    mesh_ = new Mesh();
    // "Template" particle, modify and push back into the vector to create copies of it.
    Particle p;
    for(int it = 0; it < NUM_PARTICLES; it++){
        float heightScale = pow((float)it/(NUM_PARTICLES - 1), 2.0);
        float curHeight = m_tornado->getHeight() * heightScale;
        p.position = m_tornado->interpLocal(curHeight);
        p.size = m_tornado->interpWidth(curHeight);
        particles_.push_back(p);
    }
}

TornadoParticleSystem::~TornadoParticleSystem()
{
    // Free the memory associated with particles_ by swapping with an empty vector.
    vector<Particle>().swap(particles_);
}

void TornadoParticleSystem::update(float dt)
{
    //for(int it = 0; it < NUM_PARTICLES; it++){
        //particles_[it].position = m_tornado->interp(particles_[it].position.y());
     //   particles_[it].rotation += 90 * dt;
    //}
    m_tornado->update(dt);
    for (Particle& particle : particles_) {
        //particle.position += {randf() * 10 * dt, randf() * 10 * dt, randf() * 10 * dt};
        //particle.size += 0.5 * dt;
        particle.position = m_tornado->interp(particle.position.y());
        particle.rotation += 90 * dt;
    }
}
