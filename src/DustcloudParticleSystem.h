#ifndef DUSTCLOUDPARTICLESYSTEM_H
#define DUSTCLOUDPARTICLESYSTEM_H

#include "TornadoParticleSystem.h"

class DustcloudParticleSystem : public TornadoParticleSystem
{
public:
    DustcloudParticleSystem(Tornado* tornado);
    ~DustcloudParticleSystem();
    virtual void init();
protected:
    float m_angSpeed;
    virtual vec3 getParticlePosition(Particle* p, float yval);
    virtual float getParticleSize(float yval);
    virtual float updateParticleRotation(float rot, float dt);
    virtual void spawnParticle(Particle *particle);
};

#endif // DUSTCLOUDPARTICLESYSTEM_H
