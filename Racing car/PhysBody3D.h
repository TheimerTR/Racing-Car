#ifndef __PhysBody3D_H__
#define __PhysBody3D_H__

#include "p2List.h"

#include "glmath.h"
#include <cmath>
#include "Bullet/include/btBulletDynamicsCommon.h"


class btRigidBody;
class Module;

// =================================================
struct PhysBody3D
{
	friend class ModulePhysics3D;
public:
	PhysBody3D();
	PhysBody3D(btRigidBody* body);
	~PhysBody3D();

	void Push(float x, float y, float z);
	void PushSlider(vec3 force);
	void GetTransform(float* matrix) const;
	void SetTransform(const float* matrix) const;
	void SetPos(float x, float y, float z);
	void SetAsSensor(bool is_sensor);
	btVector3 GetPosition();
	void SetinitiPos();
	btVector3 GetinitiPos();

private:

public:
	bool isSensor;
	btRigidBody* body = nullptr;
	p2List<Module*> collision_listeners;
	btVector3 INITposition;
	bool is_sensor = false;
	btCollisionShape* colShape;
	btDefaultMotionState* motionState;

};

#endif // __PhysBody3D_H__