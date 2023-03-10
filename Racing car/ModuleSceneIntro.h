#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"
#include "ModulePhysics3D.h"

#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

	void CreateLineWall(vec3 initial, vec3 final, float radius, float height, int pilarnum);

public:
	/*
	PhysBody3D* pb_snake[MAX_SNAKE];
	Sphere s_snake[MAX_SNAKE];

	PhysBody3D* pb_snake2[MAX_SNAKE];
	Sphere s_snake2[MAX_SNAKE];
	*/

	PhysBody3D* pb_chassis;
	Cube p_chassis;

	PhysBody3D* pb_wheel;
	Cylinder p_wheel;

	PhysBody3D* pb_wheel2;
	Cylinder p_wheel2;

	PhysMotor3D* left_wheel;
	PhysMotor3D* right_wheel;

	p2DynArray<Primitive*> primitives;


	PhysBody3D* pbodyA;
	PhysBody3D* pbodyB;
	PhysBody3D* pbodyC;
	PhysBody3D* pbodyD;

	Cube cubeSensor;
	PhysBody3D* sensor;

	PhysBody3D* pbodyGoal;
	PhysBody3D* pbodyGoal2;
	PhysBody3D* pbodyGoal3;
	PhysBody3D* pbodyGoal4;


	uint victory;
	uint defeat;

private:

};
