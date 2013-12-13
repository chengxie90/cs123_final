#include "cloud.h"
#include "texture.h"
#include "texturecache.h"
#include "particlematerial.h"

Cloud::Cloud(float radius)
{
    radius_ = radius;
    
    Texture* texture = TextureCache::getInstance()->acquire("cloud1", TextureType::Texture2D);
    setParticleTexture(texture);
    
    setEmissionRate(10);
    
    setMaxParticleCount(100);
    
    setRenderingOrder(RenderingOrder::YoungestFirst);
    
    ParticleMaterial* material = static_cast<ParticleMaterial *>(material_);
    material->setHorizontal(true);
}

void Cloud::spawnParticle(Particle *particle)
{
    float speed = randf(2, 10);
    vec3 velocity = {0, 0, 1};
    velocity *= speed;
    
    particle->velocity = velocity;
    
    float phi = randf(0, M_PI * 2);
    float r = radius_ * randf();
    
    float x = cosf(phi) * r;
    float y = randf() * 10;
    float z = sinf(phi) * r;
    
    particle->position = {x, y, z};
    
    particle->angularSpeed = randf(2, 15);
    
    particle->maxLife = 20;
    
    particle->size = randf(50, 150);
    
    float scale = randf(0.55, 0.6f);
    particle->color = {scale, scale, scale}; 
    
    particle->opacity = 0;
}
	
void Cloud::updateParticle(Particle &particle, float dt)
{
    particle.position += particle.velocity * dt;
    particle.rotation += particle.angularSpeed * dt;
    
    float x = particle.life / particle.maxLife;
    
    if (x < 0.5) {
        particle.opacity = x;
    }
    else {
        particle.opacity = 1 - x;
    }
    
    
}

