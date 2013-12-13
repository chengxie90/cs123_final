#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "geometry.h"
#include "sceneobject.h"

struct Particle
{
    // These rendering related properties must be declared first in this order
    vec3 position; 
    float rotation = 0; // in angle
    float size = 1;
    Color color = vec3(1.f, 1.f, 1.f);
    float opacity = 1.f;
    
    // Other properties
    float life = 0;
    float maxLife = 0;
    
    bool active = true;
    vec3 velocity;
    float angularSpeed = 0;
};

typedef vector<Particle> Particles;

enum class RenderingOrder {
    Default,
    Reversed,
    OldestFirst,
    YoungestFirst,
};
              
class ParticleSystem : public SceneObject
{
public:
    ParticleSystem();
    virtual ~ParticleSystem();
    
    virtual void renderGeometry(DrawContext &context) override;
   
    virtual void update(float dt);
    
    // to be overrided
    virtual void spawnParticle(Particle *particle);
    
    // to be overrided
    virtual void updateParticle(Particle& particle, float dt);
    
    void setParticleTexture(Texture* texture);
    
    uint32_t emissionRate() const;
    void setEmissionRate(int emissionRate);
    
    uint32_t maxParticleCount() const;
    void setMaxParticleCount(int maxParticleCount);
    
    RenderingOrder renderingOrder() const;
    void setRenderingOrder(RenderingOrder renderingOrder);
    
protected:
    vector<Particle> particles_;
    
private:
    // time elapsed since the particle system was created
    float timeElapsed_ = 0;
    
    // max number of particles allowed
    uint32_t maxParticleCount_ = 0;
    
    // number of particles per second
    uint32_t emissionRate_ = 0;
    
    float numParticlesToSpawn_ = 0;
    
    RenderingOrder renderingOrder_ = RenderingOrder::Reversed;
};

#endif // PARTICLESYSTEM_H
