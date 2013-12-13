#ifndef TORNADOPARTICLESYSTEM_H
#define TORNADOPARTICLESYSTEM_H

#include "Tornado.h"
#include "mesh.h"
#include "particlesystem.h"

class TornadoParticleSystem : public ParticleSystem
{
public:
    TornadoParticleSystem();
    TornadoParticleSystem(Tornado* tornado);
    virtual ~TornadoParticleSystem();
protected:
    int m_active_count;
    float m_lastActivation;
    int m_numParticles;
    float m_cycleSpeed;
    Tornado* m_tornado;
    virtual void init();
    virtual void update(float dt);
    virtual vec3 getParticlePosition(float yval);
    virtual float getParticleSize(float yval);
    virtual bool resetThreshold(Particle *p);
    virtual void resetParticle(Particle *p);
};

#endif // TORNADOPARTICLESYSTEM_H
