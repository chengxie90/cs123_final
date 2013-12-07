#include "GL/glew.h"
#include "particlesystem.h"
#include "meshrenderer.h"
#include "drawcontext.h"
#include "common.h"

ParticleSystem::ParticleSystem()
{
    Particle p;
    particles_.push_back(p);
    particles_.push_back(p);
    particles_.push_back(p);
    particles_.push_back(p);
    particles_.push_back(p);
    particles_.push_back(p);
    particles_.push_back(p);
    particles_.push_back(p);
    particles_.push_back(p);
    particles_.push_back(p);
    
    renderer_ = new MeshRenderer;
}

ParticleSystem::~ParticleSystem()
{
    delete renderer_;
}

void ParticleSystem::renderGeometry(DrawContext &context)
{
    update(context.deltaTime);
    
//    sort(particles_.begin(), particles_.end(), [](const Particle& lhs, const Particle& rhs) {
//        return lhs.position.z() > rhs.position.z();
//    });
    
    VertexBufferDesc desc;
    desc.bufferData = particles_.data();
    desc.bufferSize = particles_.size() * sizeof(Particle);
    desc.vertexElementSizes = {3, 3, 1};
    renderer_->setVertexBuffer(desc, PrimitiveType::Points);
    
    renderer_->render();
}

void ParticleSystem::update(float dt)
{   
    for (Particle& particle : particles_) {
        particle.position += {randf() * dt, randf() * dt, randf() * dt};
    }
}
