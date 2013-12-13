#ifndef RAINSPLASH_H
#define RAINSPLASH_H

#include "particlesystem.h"

class Terrain;

class RainSplash : public ParticleSystem
{
public:
    RainSplash(float radius, bool mist, Terrain* terrain);
    
    virtual void spawnParticle(Particle *particle) override;
    
    virtual void updateParticle(Particle &particle, float dt) override;
    
private:
    float radius_ = 0;
    
    // weak reference
    Terrain* terrain_ = NULL;
    
    float startSize_ = 0;
    float startOpacity_ = 0;
};

#endif // RAINSPLASH_H
