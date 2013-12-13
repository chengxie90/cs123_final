#include "rain.h"
#include "texture.h"
#include "texturecache.h"
#include "particlematerial.h"

Rain::Rain(float radius)
{
    radius_ = radius;
    
    Texture* texture =  TextureCache::getInstance()->acquire("rain", TextureType::Texture2D);
    setParticleTexture(texture);
    
    setEmissionRate(400);
    
    setMaxParticleCount(10000);
    
    ParticleMaterial* material = static_cast<ParticleMaterial *>(material_);
    material->setLengthScale(8);
}

void Rain::spawnParticle(Particle *particle)
{
    float speed = randf(60, 80);
    vec3 velocity = {randf(0, 0.05), -1, randf(0, 0.1)};
    velocity *= speed;
    
    particle->velocity = velocity;
    
    float phi = randf(0, M_PI * 2);
    float r = radius_ * randf();
    
    float x = cosf(phi) * r;
    float y = 0;
    float z = sinf(phi) * r;
    
    particle->position = {x, y, z};
    
    particle->maxLife = 2;
    
    particle->size = 0.07;
    
    float scale = randf(0.6f, 0.7f);
    particle->color = {scale, scale, scale};
    
    particle->opacity = randf(0.4, 0.7);
}

void Rain::updateParticle(Particle &particle, float dt)
{
    particle.position += particle.velocity * dt;
    
    particle.opacity = randf(0.4, 0.7);
}
