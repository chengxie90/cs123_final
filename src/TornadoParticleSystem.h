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
    virtual void init();
protected:
    bool m_useOpacity = true;
    bool m_randOpacity = false;
    int m_numParticles = 0;
    float m_cycleSpeed = 0;
    Tornado* m_tornado;
    virtual void update(float dt);
    virtual vec3 getParticlePosition(Particle* p, float yval);
    virtual float getParticleSize(float yval);
    virtual float updateParticleRotation(float rot, float dt);
    virtual void spawnParticle(Particle *particle);
    virtual void updateParticle(Particle& particle, float dt);
};

#endif // TORNADOPARTICLESYSTEM_H
