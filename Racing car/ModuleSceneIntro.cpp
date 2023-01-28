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

	int posx = 0;
	for (int n = 0; n < 10; n++) {
		Cylinder* c = new Cylinder();
		c->height = 1.5f;
		c->radius = 0.5f;
		c->SetPos(posx, 0.8f, 0);
		c->SetRotation(90, vec3(0, 0, 1));
		App->physics->AddBody(*c, 0);
		primitives.PushBack(c);
		posx = posx + 2;
	}

	/*vec3 initial = { -3, 0.8f, -1 };
	vec3 final = { -30, 0.8f, -50 };
	float radius = 0.5f;
	float PI = 3.14159;

		float deltax = final.x - initial.x;
		float deltaz = final.z - initial.z;
		float distance = sqrt((deltax * deltax) + (deltaz * deltaz));
		float increment = distance / (10 - 1);
		float angle = atan2(deltaz, deltax);
		for (int i = 0; i < 10; i++) {
			float x = initial.x + i * increment * cos(angle);
			float z = initial.z + i * increment * sin(angle);
			float y = 0.0;


			Cylinder* c = new Cylinder();
			c->height = 1.5f;
			c->radius = 0.5f;
			c->SetPos(x, y, z);
			c->SetRotation(90, vec3(0, 0, 1));
			App->physics->AddBody(*c, 0);
			primitives.PushBack(c);

			LOG("x: %f, z: %f, angle: %f", x, z, angle);
		}
	*/

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

