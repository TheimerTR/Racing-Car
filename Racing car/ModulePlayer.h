#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "Timer.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"
#include "ModulePhysics3D.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 1000.0f
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 1000.0f

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

public:

	PhysVehicle3D* vehicle;
	float turn = 0;
	float acceleration = 0;
	float brake = 0;

	Uint32 timer = 0;
	Timer* time;
	bool tb = false;

	bool TupD = false;
	bool TupU = false;

	bool TdowD = false;
	bool TdowU = false;

	bool wheel0 = true;
	bool wheel1 = true;
	bool wheel2 = true;
	bool wheel3 = true;

	bool mass = false;
	bool grav = false;

	bool PhysEnabled = true;

	float* initiTransform;
	VehicleInfo car;
	ModulePhysics3D* worldPhys;
	btRigidBody* body = nullptr;
};