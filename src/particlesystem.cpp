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
    // To Ken: This function can be ignored.
    update(context.deltaTime);
    
    VertexBufferDesc desc;
    desc.bufferData = particles_.data();
    desc.bufferSize = particles_.size() * sizeof(Particle);
    desc.vertexElementSizes = {3, 1, 1};
    desc.stride = sizeof(Particle);
          
    mesh_->setVertexBuffer(desc, PrimitiveType::Points);
    
    mesh_->render();
}

void ParticleSystem::update(float dt)
{   
    for (Particle& particle : particles_) {
        particle.position += {randf() * 10 * dt, randf() * 10 * dt, randf() * 10 * dt};
        particle.size += 0.5 * dt;
        particle.roation += 90 * dt;
    }
}
