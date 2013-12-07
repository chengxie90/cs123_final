#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "geometry.h"
#include "sceneobject.h"

struct Particle
{
    // These three rendering related properties must be declared first in this order
    vec3 position; 
    float roation = 0; // in angle
    float size = 1;
    
    // Other properties
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
    void update(float dt);
    Particles particles_;
    MeshRenderer *renderer_;
};

#endif // PARTICLESYSTEM_H
