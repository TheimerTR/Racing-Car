#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));


	vec3 initial;
	vec3 final;
	float radius = 0.5f;
	float height = 2.f;

	CreateLineWall(initial = { -150, 0.8f, 100 }, final = { 150, 0.8f, 100 }, radius, height, 100);
	CreateLineWall(initial = { -150, 0.8f, 130 }, final = { 160, 0.8f, 130 }, radius, height, 100);
	CreateLineWall(initial = { 152, 0.8f, 100 }, final = { 160, 0.8f, 85 }, radius, height, 6);
	CreateLineWall(initial = { 162, 0.8f, 130 }, final = { 190, 0.8f, 85 }, radius, height, 15);
	CreateLineWall(initial = { 190, 0.8f, 83 }, final = { 190, 0.8f, 25 }, radius, height, 15);
	CreateLineWall(initial = { 160, 0.8f, 83 }, final = { 160, 0.8f, 25 }, radius, height, 15);

	//Cube* cube = new Cube(); 
	//cube->size = { 10, 2, 30 }; 
	//cube->SetPos(170, 2.f, 60); 
	//cube->SetRotation(40, vec3(1, 0, 0)); 
	//primitives.PushBack(cube); 




		
	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	for (int n = 0; n < primitives.Count(); n++) {
		primitives[n]->Render();
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

void ModuleSceneIntro::CreateLineWall(vec3 initial, vec3 final, float radius, float height, int pilarnum) {

	float deltax = final.x - initial.x;
	float deltaz = final.z - initial.z;
	float distance = sqrt((deltax * deltax) + (deltaz * deltaz));
	float increment = distance / (pilarnum - 1);
	float angle = atan2(deltaz, deltax);
	for (int i = 0; i < pilarnum; i++) {
		float x = initial.x + i * increment * cos(angle);
		float z = initial.z + i * increment * sin(angle);
		float y = 0.7f;


		Cylinder* c = new Cylinder();
		c->height = height;
		c->radius = radius;
		c->color = Red; 
		c->SetPos(x, y, z);
		c->SetRotation(90, vec3(0, 0, 1));
		App->physics->AddBody(*c, 0);
		primitives.PushBack(c);
	}


}
