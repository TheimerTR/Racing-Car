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

	VehicleInfo car;

	// Car properties ----------------------------------------
	car.chassis_size.Set(2, 2, 4);
	car.chassis_offset.Set(0, 1.5, 0);
	car.mass = 500.0f;
	car.suspensionStiffness = 15.88f;
	car.suspensionCompression = 0.83f;
	car.suspensionDamping = 0.88f;
	car.maxSuspensionTravelCm = 1000.0f;
	car.frictionSlip = 50.5;
	car.maxSuspensionForce = 6000.0f;

	// Wheel properties ---------------------------------------
	float connection_height = 1.2f;
	float wheel_radius = 0.6f;
	float wheel_width = 0.5f;
	float suspensionRestLength = 1.2f;

	// Don't change anything below this line ------------------

	float half_width = car.chassis_size.x*0.5f;
	float half_length = car.chassis_size.z*0.5f;
	
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
	v1 = vehicle->vehicle->getWheelInfo(0).m_raycastInfo.m_contactNormalWS.closestAxis();
	v2 = vehicle->vehicle->getWheelInfo(1).m_raycastInfo.m_contactNormalWS.closestAxis();
	v3 = vehicle->vehicle->getWheelInfo(2).m_raycastInfo.m_contactNormalWS.closestAxis();
	v4 = vehicle->vehicle->getWheelInfo(3).m_raycastInfo.m_contactNormalWS.closestAxis();


	if (v1 != 0 && v2 != 0 && v3 != 0 && v4 != 0) {
		LOG("ALL");
		vehicle->Turn(180);
	}
	else if (v1 != 0) 
	{
		LOG("V1");
		vehicle->Turn(-180);
	}
	else if (v2 != 0)
	{
		vehicle->Turn(-180);
		LOG("V2")
	}	
	else if (v3 != 0)
	{
		vehicle->Turn(180);
		LOG("V3");
	}	
	else if (v4 != 0)
	{
		LOG("V4");
		vehicle->Turn(-180);
	}

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		time->Stop();
		time->Start();
		TupD = true;
		TupU = false;
	}

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
			if (turn < TURN_DEGREES)
				turn += TURN_DEGREES;
	}

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
			if (turn > -TURN_DEGREES)
				turn -= TURN_DEGREES;
	}

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		time->Stop();
		time->Start();
		TdowD = true;
		TdowU = false;

	}

	if (TupD) 
	{
		if (acceleration >= MAX_ACCELERATION)
		{
			acceleration = MAX_ACCELERATION;
		}
		else
		{
			acceleration = acceleration + timer;
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

		acceleration = acceleration - timer*2;
	}

	if (TdowD)
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

	vehicle->ApplyEngineForce(acceleration);
	vehicle->Turn(turn);
	vehicle->Brake(brake);

	vehicle->Render();

	char title[80];
	sprintf_s(title, "%.1f Km/h", vehicle->GetKmh());
	App->window->SetTitle(title);


	timer = time->Read();

	return UPDATE_CONTINUE;
}



