#include "wind.h"
#include "texture.h"
#include "texturecache.h"
#include "particlematerial.h"
#include "drawcontext.h"
#include "camera.h"

Wind::Wind(float radius)
{
    radius_ = radius;
    
    Texture* texture =  TextureCache::getInstance()->acquire("wind", TextureType::Texture2D);
    setParticleTexture(texture);
    
    setEmissionRate(10);
    
    setMaxParticleCount(20);
}

void Wind::spawnParticle(Particle *particle)
{
    float speed = randf(10, 20);
    vec3 velocity = {randf(0, 1), 0, randf(0, 1)};
    velocity *= speed;
    
    particle->velocity = velocity;
    
    float phi = randf(0, M_PI * 2);
    float r = radius_ * randf(0.3, 1.0);
    
    float x = cosf(phi) * r;
    float y = 0;
    float z = sinf(phi) * r;
    
    particle->position = {x, y, z};
    
    particle->maxLife = 10;
    
    particle->size = randf(10, 50);
    
    float scale = randf(0.6f, 0.8f);
    particle->color = {scale, scale * 0.9, scale * 0.85};
    
    particle->opacity = randf(0.05, 0.1);
}

void Wind::updateParticle(Particle &particle, float dt)
{
    particle.position += particle.velocity * dt;
    
    particle.opacity = randf(0.11, 0.13);
}

void Wind::renderGeometry(DrawContext &context)
{
    ParticleSystem::renderGeometry(context);
    transform().setToIdentity();
    vec3 camPos = context.camera->position();
    transform().translate(camPos.x(), camPos.y(), camPos.z());
}
	
