#ifndef DUSTCLOUDPARTICLESYSTEM_H
#define DUSTCLOUDPARTICLESYSTEM_H

#include "TornadoParticleSystem.h"

class DustcloudParticleSystem : public TornadoParticleSystem
{
public:
    DustcloudParticleSystem(Tornado* tornado);
    ~DustcloudParticleSystem();
protected:
    float m_angSpeed;
    int m_numParticles = 180;
    float m_cycleSpeed = -15.0;
    virtual void init();
    virtual vec3 getParticlePosition(Particle* p, float yval);
    virtual float getParticleSize(float yval);
    virtual float updateParticleRotation(float rot, float dt);
    virtual bool resetThreshold(Particle *p);
    virtual void resetParticle(Particle *p);
};

#endif // DUSTCLOUDPARTICLESYSTEM_H
