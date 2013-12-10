#ifndef TORNADOPARTICLESYSTEM_H
#define TORNADOPARTICLESYSTEM_H

#include "Tornado.h"
#include "mesh.h"
#include "particlesystem.h"

class TornadoParticleSystem : public ParticleSystem
{
public:
    TornadoParticleSystem(Tornado* tornado);
    virtual ~TornadoParticleSystem();
protected:
    Tornado* m_tornado;
    virtual void init();
    virtual void update(float dt);
};

#endif // TORNADOPARTICLESYSTEM_H
