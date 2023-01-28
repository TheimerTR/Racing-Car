#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	time = new Timer();

	// Car properties ----------------------------------------
	car.chassis_size.Set(3.5,3.0, 11);//Hitbox
	car.chassis1_size.Set(3.5, 0.8, 8);//base coche
	car.chassis2_size.Set(3.5, 2.0, 4);//base parte trasera
	car.chassis3_size.Set(5, 0.3, 1);//alerones delanteros
	car.chassis4_size.Set(2, 1.9, 2);//cabina
	car.chassis5_size.Set(0.2, 1, 1);//sujecion aleron izq
	car.chassis6_size.Set(0.2, 1, 1);//sujecion aleron dch
	car.chassis7_size.Set(5, 0.2, 1.3);//aleron

	car.chassis8_size.Set(1, 0.8,3.7);//Palo sujeata aleron delantero


	car.chassis_offset.Set(0, 2.4, 0.5);
	car.chassis1_offset.Set(0, 1.8, 0);
	car.chassis2_offset.Set(0, 2.4, -3);
	car.chassis3_offset.Set(0, 1.8, 5.2);
	
	car.chassis4_offset.Set(0, 2.5, -1.9);
	car.chassis5_offset.Set(1.65, 3.9, -4.5);
	car.chassis6_offset.Set(-1.65, 3.9, -4.5);
	car.chassis7_offset.Set(0, 4.4, -4.5);
	car.chassis8_offset.Set(0, 1.8, 4.5);
	

	car.mass = 250.0f;
	car.suspensionStiffness = 15.88f;
	car.suspensionCompression = 0.83f;
	car.suspensionDamping = 0.88f;
	car.maxSuspensionTravelCm = 1000.0f;
	car.frictionSlip = 50.5;
	car.maxSuspensionForce = 6000.0f;

	// Wheel properties ---------------------------------------
	float connection_height =2.0f;
	float wheel_radius = 0.6f;
	float wheel_width = 0.5f;
	float suspensionRestLength = 1.2f;

	// Don't change anything below this line ------------------

	float half_width = car.chassis1_size.x*0.5f;
	float half_length = car.chassis1_size.z*0.5f;
	
	vec3 direction(0,-1,0);
	vec3 axis(-1,0,0);
	
	car.num_wheels = 4;
	car.wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(half_width - 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[0].direction = direction;
	car.wheels[0].axis = axis;
	car.wheels[0].suspensionRestLength = suspensionRestLength;
	car.wheels[0].radius = wheel_radius;
	car.wheels[0].width = wheel_width;
	car.wheels[0].front = true;
	car.wheels[0].drive = true;
	car.wheels[0].brake = false;
	car.wheels[0].steering = true;

	// FRONT-RIGHT ------------------------
	car.wheels[1].connection.Set(-half_width + 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[1].direction = direction;
	car.wheels[1].axis = axis;
	car.wheels[1].suspensionRestLength = suspensionRestLength;
	car.wheels[1].radius = wheel_radius;
	car.wheels[1].width = wheel_width;
	car.wheels[1].front = true;
	car.wheels[1].drive = true;
	car.wheels[1].brake = false;
	car.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	car.wheels[2].connection.Set(half_width - 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[2].direction = direction;
	car.wheels[2].axis = axis;
	car.wheels[2].suspensionRestLength = suspensionRestLength;
	car.wheels[2].radius = wheel_radius;
	car.wheels[2].width = wheel_width;
	car.wheels[2].front = false;
	car.wheels[2].drive = false;
	car.wheels[2].brake = true;
	car.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	car.wheels[3].connection.Set(-half_width + 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[3].direction = direction;
	car.wheels[3].axis = axis;
	car.wheels[3].suspensionRestLength = suspensionRestLength;
	car.wheels[3].radius = wheel_radius;
	car.wheels[3].width = wheel_width;
	car.wheels[3].front = false;
	car.wheels[3].drive = false;
	car.wheels[3].brake = true;
	car.wheels[3].steering = false;

	vehicle = App->physics->AddVehicle(car);
	vehicle->SetPos(0, 12, 10);

	vehicle->SetinitiPos();

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
	{
		vehicle->ResetCar();
	}

	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
	{
		App->camera->freeCam = !App->camera->freeCam;
	}

	if (App->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN) 
	{
		PhysEnabled = !PhysEnabled;
		if (PhysEnabled) 
		{
			LOG("Physics: True");
		}		
		if (!PhysEnabled) 
		{
			LOG("Physics: False");
		}
	}

	if (PhysEnabled) 
	{

		wheel0 = vehicle->vehicle->getWheelInfo(0).m_raycastInfo.m_groundObject;
		wheel1 = vehicle->vehicle->getWheelInfo(1).m_raycastInfo.m_groundObject;
		wheel2 = vehicle->vehicle->getWheelInfo(2).m_raycastInfo.m_groundObject;
		wheel3 = vehicle->vehicle->getWheelInfo(3).m_raycastInfo.m_groundObject;

		if (App->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN) {
			mass = !mass;
		}

		if (App->input->GetKey(SDL_SCANCODE_G) == KEY_DOWN) {
			grav = !grav;
		}

		if (mass == true)
		{
			if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
			{
				car.mass = 100.0f;
				mass = false;
				LOG("Mass: %f", car.mass);
			}
			if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
			{
				car.mass = 200.0f;
				mass = false;
				LOG("Mass: %f", car.mass);
			}
			if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
			{
				car.mass = 300.0f;
				mass = false;
				LOG("Mass: %f", car.mass);
			}
			if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
			{
				car.mass = 400.0f;
				mass = false;
				LOG("Mass: %f", car.mass);
			}
			if (App->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN)
			{
				car.mass = 500.0f;
				mass = false;
				LOG("Mass: %f", car.mass);
			}
			if (App->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN)
			{
				car.mass = 600.0f;
				mass = false;
				LOG("Mass: %f", car.mass);
			}
			if (App->input->GetKey(SDL_SCANCODE_7) == KEY_DOWN)
			{
				car.mass = 700.0f;
				mass = false;
				LOG("Mass: %f", car.mass);
			}
			if (App->input->GetKey(SDL_SCANCODE_8) == KEY_DOWN)
			{
				car.mass = 800.0f;
				mass = false;
				LOG("Mass: %f", car.mass);
			}
			if (App->input->GetKey(SDL_SCANCODE_9) == KEY_DOWN)
			{
				car.mass = 900.0f;
				mass = false;
				LOG("Mass: %f", car.mass);
			}
			if (App->input->GetKey(SDL_SCANCODE_0) == KEY_DOWN)
			{
				car.mass = 1000.0f;
				mass = false;
				LOG("Mass: %f", car.mass);
			}
		}

		if (grav == true)
		{
			if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
			{
				App->physics->world->setGravity(btVector3(0.0f, -1.0f, 0.0f));
				grav = false;
				LOG("GRAVITY: -1");
			}
			if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
			{
				App->physics->world->setGravity(btVector3(0.0f, -2.0f, 0.0f));
				grav = false;
				LOG("GRAVITY: -2");
			}
			if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
			{
				App->physics->world->setGravity(btVector3(0.0f, -3.0f, 0.0f));
				grav = false;
				LOG("GRAVITY: -3");
			}
			if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
			{
				App->physics->world->setGravity(btVector3(0.0f, -4.0f, 0.0f));
				grav = false;
				LOG("GRAVITY: -4");
			}
			if (App->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN)
			{
				App->physics->world->setGravity(btVector3(0.0f, -5.0f, 0.0f));
				grav = false;
				LOG("GRAVITY: -5");
			}
			if (App->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN)
			{
				App->physics->world->setGravity(btVector3(0.0f, -6.0f, 0.0f));
				grav = false;
				LOG("GRAVITY: -6");
			}
			if (App->input->GetKey(SDL_SCANCODE_7) == KEY_DOWN)
			{
				App->physics->world->setGravity(btVector3(0.0f, -7.0f, 0.0f));
				grav = false;
				LOG("GRAVITY: -7");
			}
			if (App->input->GetKey(SDL_SCANCODE_8) == KEY_DOWN)
			{
				App->physics->world->setGravity(btVector3(0.0f, -8.0f, 0.0f));
				grav = false;
				LOG("GRAVITY: -8");
			}
			if (App->input->GetKey(SDL_SCANCODE_9) == KEY_DOWN)
			{
				App->physics->world->setGravity(btVector3(0.0f, -9.0f, 0.0f));
				grav = false;
				LOG("GRAVITY: -9");
			}
			if (App->input->GetKey(SDL_SCANCODE_0) == KEY_DOWN)
			{
				App->physics->world->setGravity(btVector3(0.0f, -10.0f, 0.0f));
				grav = false;
				LOG("GRAVITY: -10");
			}
		}
		if (wheel0 != 1 && wheel1 != 1 && wheel2 != 1 && wheel3 != 1) 
		{

		}
		else if (wheel0 != 1 && wheel2 != 1)
		{

			vehicle->ResetInitPos();
		}
		else if (wheel1 != 1 && wheel3 != 1)
		{

			vehicle->ResetInitPos();
		}

		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN) {
			time->Stop();
			time->Start();
			TupD = true;
			TupU = false;
		}
		
		//Cuanto mas tiempo se mantenga pulsado mas acelera
		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		{
			if (acceleration >= MAX_ACCELERATION)
			{
				acceleration = MAX_ACCELERATION;
			}
			else
			{
				acceleration = (acceleration + (timer * 2)) / (car.mass * 0.001);
			}
		}

		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		{
			if (turn < TURN_DEGREES)
				turn += TURN_DEGREES;
		}

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		{
			if (turn > -TURN_DEGREES)
				turn -= TURN_DEGREES;
		}

		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN) {

			time->Stop();
			time->Start();
			TdowD = true;
			TdowU = false;
		}

		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		{
			if (acceleration <= -MAX_ACCELERATION)
			{
				acceleration = -MAX_ACCELERATION;
			}
			else
			{
				acceleration = acceleration - timer;
			}
		}

		if (!TdowD)
		{
			if (acceleration <= 0)
			{
				brake = 6;
				acceleration = 0;
				TupU = false;
			}
			if (!TupD)
			{
				if (acceleration >= 2)
				{
					acceleration = (acceleration - (timer * 4)) / (car.mass * 0.001);
				}
			}
		}

		if (!TupD)
		{
			if (acceleration >= 0)
			{
				brake = 6;
				acceleration = 0;
				TdowU = false;
			}
			if (!TdowD)
			{
				if (acceleration <= -2)
				{
					acceleration = acceleration + timer * 2;
				}
			}
		}

		if (TupU)
		{
			if (acceleration <= 0)
			{
				brake = 6;
				acceleration = 0;
				TupU = false;
			}

			acceleration = (acceleration - (timer * 4)) / (car.mass * 0.001);
		}

		if (TdowU)
		{
			if (acceleration >= 0)
			{
				brake = 6;
				acceleration = 0;
				TdowU = false;
			}

			acceleration = acceleration + timer * 2;
		}

		//LOG("Acceleration: %f", acceleration);

		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_UP)
		{
			if (acceleration > 0.0f)
			{
				TupD = false;
				time->Start();
				TupU = true;
			}
		}

		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
		{
			if (acceleration < 0.0f)
			{
				TdowD = false;
				time->Start();
				TdowU = true;
			}
		}

		if ((App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP) || (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP))
		{
			turn = 0;
		}

		timer = time->ReadCar();
	}
	else 
	{
		turn = acceleration = brake = 0.0f;

		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		{
			acceleration = MAX_ACCELERATION;
		}

		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		{
			if (turn < TURN_DEGREES)
				turn += TURN_DEGREES;
		}

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		{
			if (turn > -TURN_DEGREES)
				turn -= TURN_DEGREES;
		}

		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		{
			brake = BRAKE_POWER;
		}
	}
	
	//Aqui supongo que habria que calcular el drag
	vehicle->GetKmh();
	float drag= ((vehicle->GetKmh()/3.6)* (vehicle->GetKmh() / 3.6)/2) * (1.21) * (0.25); //v en m/s al cuadrado x densidad aire kg/m3 x coeficiente FUYM
	vehicle->ApplyEngineForce(acceleration-drag);
	vehicle->Turn(turn);
	vehicle->Brake(brake);

	vehicle->Render();

	char title[80];
	sprintf_s(title, "%.1f Km/h", vehicle->GetKmh());
	App->window->SetTitle(title);

	return UPDATE_CONTINUE;
}



