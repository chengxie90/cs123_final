#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "geometry.h"
#include "sceneobject.h"

struct Particle
{
    vec3 position;
    vec3 velocity;
};

typedef vector<Particle> Particles;
              
class ParticleSystem : public SceneObject
{
public:
    ParticleSystem();
    virtual ~ParticleSystem();
    
    virtual void renderGeometry(DrawContext &context) override; 
    
private:
    Particles particles_;
    
};

#endif // PARTICLESYSTEM_H
