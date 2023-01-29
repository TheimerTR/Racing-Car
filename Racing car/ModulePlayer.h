#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "Timer.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"
#include "ModulePhysics3D.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 2000.0f //Cambiando a 200 (era 1000.0f)
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 2000.0f

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

public:

	PhysVehicle3D* vehicle;
	float turn = 0;
	float acceleration = 0;
	float brake = 0;

	Uint32 timer = 0;
	Uint32 tW = 0;
	Uint32 timeL = 0;
	Timer* time;
	Timer* TimWait;
	Timer* TimerLose;
	bool tb = false;
	bool wait = false;
	bool All = false;

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

	bool win;
	bool SlowArea = false;
	bool fxwin = false;
};