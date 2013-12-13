#include "GL/glew.h"
#include "particlesystem.h"
#include "mesh.h"
#include "drawcontext.h"
#include "common.h"
#include "particlematerial.h"

ParticleSystem::ParticleSystem()
{   
    mesh_ = new Mesh;
}

ParticleSystem::~ParticleSystem()
{
    delete mesh_;
}

// To Ken: This function can be ignored.
void ParticleSystem::renderGeometry(DrawContext &context)
{   
    update(context.deltaTime);
    
    VertexBufferDesc desc;
    desc.bufferData = particles_.data();
    desc.bufferSize = particles_.size() * sizeof(Particle);
    desc.vertexElementSizes = {3, 1, 1};
    desc.stride = sizeof(Particle);
          
    mesh_->setVertexBuffer(desc, PrimitiveType::Points);
    
    mesh_->render();
}

void ParticleSystem::setParticleTexture(Texture *texture)
{
    ParticleMaterial* material = new ParticleMaterial;
    material->setTexture(texture);
    setMaterial(material);
}

void ParticleSystem::update(float dt)
{   
    for (Particle& particle : particles_) {
        particle.position += {randf() * 10 * dt, randf() * 10 * dt, randf() * 10 * dt};
        particle.size += 0.5 * dt;
        particle.rotation += 90 * dt;
    }
}
