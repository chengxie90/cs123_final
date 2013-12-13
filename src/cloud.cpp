#include "cloud.h"
#include "texture.h"
#include "texturecache.h"
#include "particlematerial.h"

Cloud::Cloud(float radius)
{
    radius_ = radius;
    
    Texture* texture = TextureCache::getInstance()->acquire("cloud2", TextureType::Texture2D);
    setParticleTexture(texture);
    
    setEmissionRate(10);
    
    setMaxParticleCount(1000);
    
    ParticleMaterial* material = static_cast<ParticleMaterial *>(material_);
    material->setHorizontal(true);
}

void Cloud::spawnParticle(Particle *particle)
{
    float speed = randf(5, 15);
    vec3 velocity = {0, 0, 1};
    velocity *= speed;
    
    particle->velocity = velocity;
    
    float phi = randf(0, M_PI * 2);
    float r = radius_ * randf();
    
//    float x = randf(-radius_, radius_);
//    float z = randf(-radius_, radius_);
    
    float x = cosf(phi) * r;
    float y = randf() * 10;
    float z = sinf(phi) * r;
    
    particle->position = {x, y, z};
    
    particle->rotation = randf(180, 360);
    
    particle->maxLife = 20;
    
    particle->size = randf(50, 150);
    
    float scale = randf(0.6, 0.7f);
    particle->color = {scale, scale, scale}; 
    
    particle->opacity = 0;
}
	
void Cloud::updateParticle(Particle &particle, float dt)
{
    particle.position += particle.velocity * dt;
    
    float x = particle.life / particle.maxLife;
    
    if (x < 0.5) {
        particle.opacity = x;
    }
    else {
        particle.opacity = 1 - x;
    }
    
    
}

