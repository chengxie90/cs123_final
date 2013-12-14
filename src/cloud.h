#ifndef CLOUD_H
#define CLOUD_H

#include "particlesystem.h"

class Cloud : public ParticleSystem
{
public:
    Cloud(float radius);
    
    virtual void spawnParticle(Particle *particle) override;
    
    virtual void updateParticle(Particle &particle, float dt) override;

private:
    float radius_;
};

#endif // CLOUD_H
