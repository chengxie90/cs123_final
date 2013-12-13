#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "geometry.h"
#include "sceneobject.h"

struct Particle
{
    // These three rendering related properties must be declared first in this order
    vec3 position; 
    float rotation = 0; // in angle
    float size = 1;
    bool active = true;
    
    // Other properties
    vec3 velocity;
    vec3 somethingelse;
};

typedef vector<Particle> Particles;
              
class ParticleSystem : public SceneObject
{
public:
    ParticleSystem();
    virtual ~ParticleSystem();
    
    virtual void renderGeometry(DrawContext &context) override;
    
    void setParticleTexture(Texture* texture);

    virtual void update(float dt);
    vector<Particle> particles_;
    
    int numParticlesMax_;
    int emissionRate_;
};

#endif // PARTICLESYSTEM_H
