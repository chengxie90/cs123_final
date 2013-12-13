#ifndef RAIN_H
#define RAIN_H

#include "particlesystem.h"

class Rain : public ParticleSystem
{
public:
    Rain(float radius);
    
    virtual void spawnParticle(Particle *particle) override;
    
    virtual void updateParticle(Particle &particle, float dt) override;
    
    virtual void renderGeometry(DrawContext &context) override;
    
private:
    float radius_;
};

#endif // RAIN_H
