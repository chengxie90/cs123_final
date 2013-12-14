#ifndef WIND_H
#define WIND_H

#include "particlesystem.h"

class Wind : public ParticleSystem
{
public:
    Wind(float radius);
    
    virtual void spawnParticle(Particle *particle) override;
    
    virtual void updateParticle(Particle &particle, float dt) override;
    
    virtual void renderGeometry(DrawContext &context) override;

private:
    float radius_;

};

#endif // WIND_H
