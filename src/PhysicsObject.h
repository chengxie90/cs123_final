#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

#include "sceneobject.h"

class Terrain;
class PhysicsObject;

struct PhysicsCollection{
    float gravity = 10.0;
    Terrain* terrain;
    vector<PhysicsObject*> objects;
};

class PhysicsObject : public SceneObject
{
public:
    PhysicsObject(PhysicsCollection *phys);
    virtual ~PhysicsObject();
    vec3 getVelocity(){return m_velocity;}
    vec3 getAngleVelocity(){return m_angleVelocity;}
    float getPhysicsRadius(){return m_physicsRadius;}
    void setPhysicsRadius(float rad){m_physicsRadius = rad;}
    void addVelocity(vec3 vel){m_velocity += vel;}
    void addAngleVelocity(vec3 avel){m_angleVelocity += avel;}
    void setMeshScale(float scl){m_meshScale = scl;}
    void setPosition(vec3 pos);
    bool isGravityEnabled(){return m_gravityEnabled;}
    void setGravity(bool b){m_gravityEnabled = b;}
    vec3 getWorldPosition();
    bool collideGround(vec3 pos);
    bool collideObject(PhysicsObject* obj);
    virtual void update(float dt);
protected:
    PhysicsCollection* m_phys = NULL;
    float m_physicsRadius;
    float m_meshScale;
    vec3 m_velocity;
    vec3 m_angleVelocity;
    bool m_gravityEnabled = true;
};

#endif // PHYSICSOBJECT_H
