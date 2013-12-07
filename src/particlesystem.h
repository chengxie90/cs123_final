#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "geometry.h"
#include "sceneobject.h"

struct Particle
{
    vec3 position;
    vec3 velocity;
    float size = 1;
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
