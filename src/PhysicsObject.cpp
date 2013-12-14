#include "PhysicsObject.h"
#include "terrain.h"

PhysicsObject::PhysicsObject(PhysicsCollection* phys)
{
    m_phys = phys;
    m_velocity = {0, 0, 0};
    m_angleVelocity = {0, 0, 0};
    m_meshScale = 1.0;
    m_physicsRadius = 5.0;
}

PhysicsObject::~PhysicsObject()
{
}

void PhysicsObject::setPosition(vec3 pos)
{
    transform().setToIdentity();
    transform().translate(pos);
    transform().scale(m_meshScale);
}

vec3 PhysicsObject::getWorldPosition()
{
    return transform().column(3).toVector3D();
}

bool PhysicsObject::collideGround(vec3 pos)
{
    float yter = m_phys->terrain->height(pos.x(), pos.z());
    return pos.y() <= yter + m_physicsRadius;
}

bool PhysicsObject::collideObject(PhysicsObject *obj)
{
    vec3 objPos= obj->getWorldPosition();
    float diff = (getWorldPosition() - objPos).length();
    float bound = m_physicsRadius + obj->getPhysicsRadius();
    return diff < bound;
}

void PhysicsObject::update(float dt)
{
    vec3 next = getWorldPosition() + m_velocity * dt;
    if(collideGround(next)){
        // Teleport above the ground!
        float yter = m_phys->terrain->height(next.x(), next.z());
        next.setY(yter + m_physicsRadius);
        m_velocity = {0.0, 0.0, 0.0};
        setGravity(false);
    }
    setPosition(next);

}
