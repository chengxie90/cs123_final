#ifndef SPLASHPARTICLESYSTEM_H
#define SPLASHPARTICLESYSTEM_H

#include "TornadoParticleSystem.h"

class SplashParticleSystem : public TornadoParticleSystem
{
public:
    SplashParticleSystem(Tornado* tornado);
    ~SplashParticleSystem();
    virtual void init();
protected:
    float m_angSpeed;
    virtual vec3 getParticlePosition(Particle* p, float yval);
    virtual float getParticleSize(float yval);
    virtual float updateParticleRotation(float rot, float dt);
    virtual void spawnParticle(Particle *particle);
};

#endif // SPLASHPARTICLESYSTEM_H
