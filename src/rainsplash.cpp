#include "rainsplash.h"
#include "texture.h"
#include "texturecache.h"
#include "particlematerial.h"
#include "terrain.h"
#include "drawcontext.h"
#include "camera.h"

RainSplash::RainSplash(float radius, bool mist, Terrain* terrain)
{
    radius_ = radius;
    terrain_ = terrain;
    
    Texture* texture = NULL;
    ParticleMaterial* material = static_cast<ParticleMaterial *>(material_);
    
    if (mist) {
        texture = TextureCache::getInstance()->acquire("rainmist", TextureType::Texture2D);
        material->setHorizontal(false);
    }
    else {
        texture = TextureCache::getInstance()->acquire("raindrop", TextureType::Texture2D);
        material->setHorizontal(true);
    }

    setParticleTexture(texture);
    
    setEmissionRate(8000);
    
    setMaxParticleCount(40000);
}

void RainSplash::spawnParticle(Particle *particle)
{
    float phi = randf(0, M_PI * 2);
    float r = radius_ * randf(0, 1.0);
    
    float x = cosf(phi) * r + cameraPosition_.x();
    float z = sinf(phi) * r + cameraPosition_.z();
    float y = terrain_->height(x, z) + 0.1;
   
    particle->position = {x, y, z};
    
    particle->maxLife = randf(0.4, 0.6);
    
    particle->size = startSize_ = randf(0.2, 0.3);
    
    float c = randf(0.6, 0.9);
    particle->color = {c, c, c};
    
    particle->opacity = startOpacity_ = randf(0.6, 0.8);
    
    startSize_ = 0.2;
}

void RainSplash::updateParticle(Particle &particle, float dt)
{
    float x = particle.life / particle.maxLife;
    particle.size = linear_interpolate(startSize_, startSize_ + 0.15, x);
    particle.opacity = startOpacity_ * (1 - x);
    
}

void RainSplash::renderGeometry(DrawContext &context)
{
    ParticleSystem::renderGeometry(context);
    transform().setToIdentity();
    cameraPosition_ = context.camera->position();
}
