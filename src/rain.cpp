#include "rain.h"
#include "texture.h"
#include "texturecache.h"
#include "particlematerial.h"
#include "drawcontext.h"
#include "camera.h"

Rain::Rain(float radius)
{
    radius_ = radius;
    
    Texture* texture =  TextureCache::getInstance()->acquire("rain", TextureType::Texture2D);
    setParticleTexture(texture);
    
    setEmissionRate(4000);
    
    setMaxParticleCount(20000);
    
    ParticleMaterial* material = static_cast<ParticleMaterial *>(material_);
    material->setLengthScale(12);
}

void Rain::spawnParticle(Particle *particle)
{
    float speed = randf(60, 100);
    vec3 velocity = {randf(0, 0.05), -1, randf(0, 0.1)};
    velocity *= speed;
    
    particle->velocity = velocity;
    
    float phi = randf(0, M_PI * 2);
    float r = radius_ * randf(0.3, 1.0);
    
    float x = cosf(phi) * r;
    float y = 0;
    float z = sinf(phi) * r;
    
    particle->position = {x, y, z};
    
    particle->maxLife = 2;
    
    particle->size = 0.08;
    
    float scale = randf(0.6f, 0.8f);
    particle->color = {scale, scale * 0.9, scale * 0.85};
    
    particle->opacity = randf(0.4, 0.7);
}

void Rain::updateParticle(Particle &particle, float dt)
{
    particle.position += particle.velocity * dt;
    particle.opacity = randf(0.4, 0.7);
}

void Rain::renderGeometry(DrawContext &context)
{
    ParticleSystem::renderGeometry(context);
    transform().setToIdentity();
    vec3 camPos = context.camera->position();
    transform().translate(camPos.x(), camPos.y() + 50, camPos.z());
}


