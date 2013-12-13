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
    virtual void init();
    virtual vec3 getParticlePosition(float yval);
    virtual float getParticleSize(float yval);
};

#endif // DUSTCLOUDPARTICLESYSTEM_H
