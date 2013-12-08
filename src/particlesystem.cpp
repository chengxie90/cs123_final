#include "GL/glew.h"
#include "particlesystem.h"
#include "mesh.h"
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
    
    mesh_ = new Mesh;
}

ParticleSystem::~ParticleSystem()
{
    delete mesh_;
}

void ParticleSystem::renderGeometry(DrawContext &context)
{
    update(context.deltaTime);
    
    // This is incorrect, should be sorted in view space
//    sort(particles_.begin(), particles_.end(), [](const Particle& lhs, const Particle& rhs) {
//        return lhs.position.z() > rhs.position.z();
//    });
    
    VertexBufferDesc desc;
    desc.bufferData = particles_.data();
    desc.bufferSize = particles_.size() * sizeof(Particle);
    desc.vertexElementSizes = {3, 1, 1, sizeof(Particle) / sizeof(float) - 5};
    mesh_->setVertexBuffer(desc, PrimitiveType::Points);
    
    mesh_->render();
}

void ParticleSystem::update(float dt)
{   
    for (Particle& particle : particles_) {
        particle.position += {randf() * dt, randf() * dt, randf() * dt};
        particle.size += 0.5 * dt;
        particle.roation += 90 * dt;
    }
}
