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
	float height = 2.5f;

	CreateLineWall(initial = { -150, 52.8f, 100 }, final = { 150, 52.8f, 100 }, radius, height, 100);
	CreateLineWall(initial = { -150, 52.8f, 130 }, final = { 160, 52.8f, 130 }, radius, height, 100);
	CreateLineWall(initial = { 152, 52.8f, 100 }, final = { 160, 52.8f, 85 }, radius, height, 6);
	CreateLineWall(initial = { 162, 52.8f, 130 }, final = { 190, 52.8f, 85 }, radius, height, 15);
	CreateLineWall(initial = { 190, 52.8f, 83 }, final = { 190, 52.8f, 25 }, radius, height, 15);
	CreateLineWall(initial = { 160, 52.8f, 83 }, final = { 160, 52.8f, 25 }, radius, height, 15);
	CreateLineWall(initial = { 160, 52.8f, 23 }, final = { 147, 52.8f, 15 }, radius, height, 6);
	CreateLineWall(initial = { 190, 52.8f, 23 }, final = { 180, 52.8f, 10 }, radius, height, 6);
	CreateLineWall(initial = { 147, 52.8f, 13 }, final = { 147, 52.8f, -200 }, radius, height, 55);
	CreateLineWall(initial = { 180, 52.8f, 8 }, final = { 180, 52.8f, -220 }, radius, height, 60);
	CreateLineWall(initial = { 147, 52.8f, -200 }, final = { 130, 52.8f, -225 }, radius, height, 7);
	CreateLineWall(initial = { 180, 52.8f, -222 }, final = { 170, 52.8f, -260 }, radius, height, 9);
	CreateLineWall(initial = { 170, 52.8f, -260 }, final = { -150, 52.8f, -260 }, radius, height, 90);
	CreateLineWall(initial = { 128, 52.8f, -224 }, final = { -50, 52.8f, -225 }, radius, height, 70);
	CreateLineWall(initial = { -50, 52.8f, -223 }, final = { -50, 52.8f, -100 }, radius, height, 60);
	CreateLineWall(initial = { -75, 52.8f, -223 }, final = { -75, 52.8f, -100 }, radius, height, 60);
	CreateLineWall(initial = { -150, 52.8f, -258 }, final = { -150, 52.8f, -100 }, radius, height, 80);


	Cube* ground1 = new Cube(); 
	ground1->size = { 1000, 2, 500 };
	ground1->SetPos(170, 50, 200);
	ground1->color = Green; 
	App->physics->AddBody(*ground1, 0);
	primitives.PushBack(ground1);

	Cube* ground2 = new Cube();
	ground2->size = { 50, 2, 250 };
	ground2->SetPos(170, 50, -200);
	ground2->color = Blue;
	App->physics->AddBody(*ground2, 0);
	primitives.PushBack(ground2);

	Cube* ground3 = new Cube();
	ground3->size = { 200, 2, 300 };
	ground3->SetPos(50, 50, -200);
	ground3->color = Blue;
	App->physics->AddBody(*ground3, 0);
	primitives.PushBack(ground3);

	Cube* cube = new Cube(); 
	cube->size = { 10, 2, 30 }; 
	cube->SetPos(170, 55.f, -10); 
	cube->SetRotation(20, vec3(1, 0, 0)); 
	App->physics->AddBody(*cube, 0);

	primitives.PushBack(cube); 


	//constraint slider

	Cube* bodyA;
	bodyA = new Cube();
	bodyA->size = { 12.3, 5, 0.5 };
	bodyA->color = Green;
	bodyA->SetPos(0,61.7, 20);
	pbodyA = App->physics->AddBody(*bodyA, 1000);
	primitives.PushBack(bodyA);
	

	Cube* bodyB;
	bodyB = new Cube();
	bodyB->size = { 12.3, 0.8, 0.8 };
	bodyB->SetPos(0, 60, 20);
	pbodyB = App->physics->AddBody(*bodyB, 0);
	primitives.PushBack(bodyB);

	btTransform frameInA;
	frameInA.getBasis().setEulerZYX(0, 0, M_PI / 2);
	frameInA.setOrigin(btVector3(0, 0, 0));

	btTransform frameInB;
	frameInB.getBasis().setEulerZYX(0, 0, M_PI / 2);
	frameInB.setOrigin(btVector3(0, 0, 0));

	App->physics->AddConstraintSlider(*pbodyA, *pbodyB, frameInA, frameInB);

	Cube* bodyC;
	bodyC = new Cube();
	bodyC->size = { 12.3, 5, 0.5 };
	bodyC->color = Green;
	bodyC->SetPos(20, 61.7, 20);
	pbodyC = App->physics->AddBody(*bodyC, 1000);
	primitives.PushBack(bodyC);


	Cube* bodyD;
	bodyD = new Cube();
	bodyD->size = { 12.3, 0.8, 0.8 };
	bodyD->SetPos(20, 60, 20);
	pbodyD = App->physics->AddBody(*bodyD, 0);
	primitives.PushBack(bodyD);

	btTransform frameInC;
	frameInC.getBasis().setEulerZYX(0, 0, M_PI / 2);
	frameInC.setOrigin(btVector3(0, 0, 0));

	btTransform frameInD;
	frameInD.getBasis().setEulerZYX(0, 0, M_PI / 2);
	frameInD.setOrigin(btVector3(0, 0, 0));


	App->physics->AddConstraintSlider(*pbodyC, *pbodyD, frameInC, frameInD);
		
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

	if (App->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN)
	{

		pbodyA->Push(0, -5000, 0);

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
		float y = initial.y;


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
