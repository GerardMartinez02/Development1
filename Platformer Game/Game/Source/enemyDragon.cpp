
#include "enemyDragon.h"
#include "Animation.h"
#include "App.h"
#include "Audio.h"
#include "Render.h"
#include "ModulePlayer.h"
#include "Input.h"
#include "Textures.h"
#include "Module.h"
#include "ModulePhysics.h"
#include "Map.h"
#include "Pathfinding.h"

#include <stdlib.h>
#include "Defs.h"
#include "Log.h"

EnemyDragon::EnemyDragon()
{
	name.Create("Enemy");

	idleRightDragon.PushBack({ 5, 13, 28, 26 });

	//idleAnimLeft
	idleLeftDragon.PushBack({ 168, 139, 28, 27 });

	//rightAnim
	leftDragon.PushBack({ 5, 41, 29, 27 });
	leftDragon.PushBack({ 33, 42, 30, 27 });
	leftDragon.PushBack({ 62, 42, 28, 27 });
	leftDragon.PushBack({ 90, 41, 28, 28 });
	leftDragon.PushBack({ 118, 42, 28, 27 });
	leftDragon.PushBack({ 146, 41, 28, 28 });
	leftDragon.loop = true;
	leftDragon.speed = 0.1f;


	//leftAnim
	rightDragon.PushBack({ 167, 167, 29, 27 });
	rightDragon.PushBack({ 138, 168, 30, 27 });
	rightDragon.PushBack({ 111, 167, 28, 27 });
	rightDragon.PushBack({ 83, 167, 28, 28 });
	rightDragon.PushBack({ 55, 168, 28, 27 });
	rightDragon.PushBack({ 27, 167, 28, 28 });
	rightDragon.loop = true;
	rightDragon.speed = 0.1f;

}
EnemyDragon::~EnemyDragon()
{

}

bool EnemyDragon::Awake(pugi::xml_node& config)
{
	LOG("Loading Enemy");
	bool ret = true;
	//textureBird.Create(config.child("textureBird").child_value());

	//intitialDragonPosition.x = config.child("startPositionBird").attribute("x").as_int();
	//intitialDragonPosition.y = config.child("startPositionBird").attribute("y").as_int();

	// Enemy's speed
	speed = config.child("speed").attribute("value").as_int();
	return ret;
}

// Called before the first frame
bool EnemyDragon::Start()
{
	// Load enemies
	destroyedDragon = false;

	bird = app->tex->Load("Assets/textures/enemies/DragonEnemy.png");

	// stating animation

	currentDragonAnimation = &idleLeftDragon;

	intitialDragonPosition = app->map->MapToWorld(129, 65);

	//intitialDragonPosition.x = 5;
	//intitialDragonPosition.y = 69;

	dragonPosition.x = intitialDragonPosition.x;
	dragonPosition.y = intitialDragonPosition.y;

	int  Hitbox[16] =
	{
		0, 2,
		0, 24,
		2, 26,
		24, 26,
		26, 24,
		26, 2,
		24, 0,
		2, 0
	};


	dragonBody = app->physics->CreateEnemyDragon(dragonPosition.x , dragonPosition.y , Hitbox, 16, 0);
	dragonBody->listener = this;
	dragonBody->type = typeOfCollision::DRAGON;
	dragonDead = false;

	return true;
}

// Called each loop iteration
bool EnemyDragon::PreUpdate()
{
	/*OPTICK_CATEGORY("lvl1 PreUpdate", Optick::Category::Scene);*/
	return true;
}

// Called each loop iteration
bool EnemyDragon::Update(float dt)
{

	if (dragonDead == false)
	{
		if (app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)
		{
			dragonBody->body->SetTransform({ PIXEL_TO_METERS(dragonPosition.x), PIXEL_TO_METERS(dragonPosition.y) }, 0.0f);
		}

		dragonVelocity = dragonBody->body->GetLinearVelocity();

		dragonBody->body->SetLinearVelocity(dragonVelocity);

		if (dragonPosition.DistanceTo(app->player->position) < 250)
		{
			if (dragonPosition.x < app->player->position.x)
			{
				currentDragonAnimation = &leftDragon;
				dragonBody->body->SetLinearVelocity({ 0.7f,0.0f });

			}
			if (dragonPosition.x > app->player->position.x)
			{
				currentDragonAnimation = &rightDragon;
				dragonBody->body->SetLinearVelocity({ -0.7f,0.0f });

			}
			if (dragonPosition.y > app->player->position.y)
			{
				dragonBody->body->SetLinearVelocity({ 0.0f,-0.7f });
			}
			if (dragonPosition.y < app->player->position.y)
			{
				dragonBody->body->SetLinearVelocity({ 0.0f,0.7f });
			}
			if (dragonPosition.x < app->player->position.x && dragonPosition.y > app->player->position.y)
			{
				currentDragonAnimation = &leftDragon;
				dragonBody->body->SetLinearVelocity({ 0.7f,-0.7f });

			}
			if (dragonPosition.x > app->player->position.x && dragonPosition.y > app->player->position.y)
			{
				currentDragonAnimation = &rightDragon;
				dragonBody->body->SetLinearVelocity({ -0.7f,-0.7f });

			}
			if (dragonPosition.x < app->player->position.x && dragonPosition.y < app->player->position.y)
			{
				currentDragonAnimation = &leftDragon;
				dragonBody->body->SetLinearVelocity({ 0.7f,0.7f });

			}
			if (dragonPosition.x > app->player->position.x && dragonPosition.y < app->player->position.y)
			{
				currentDragonAnimation = &rightDragon;
				dragonBody->body->SetLinearVelocity({ -0.7f,0.7f });

			}
		}
		else
		{
			if (dragonPosition.x == intitialDragonPosition.x && dragonPosition.y == intitialDragonPosition.y)
			{
				if (currentDragonAnimation == &leftDragon)
				{
					currentDragonAnimation = &idleRightDragon;
					dragonBody->body->SetLinearVelocity({ 0.0f,0.0f });
				}
				if (currentDragonAnimation == &rightDragon)
				{
					currentDragonAnimation = &idleLeftDragon;
					dragonBody->body->SetLinearVelocity({ 0.0f,0.0f });
				}
			}
			if (dragonPosition.x < intitialDragonPosition.x)
			{
				currentDragonAnimation = &leftDragon;
				dragonBody->body->SetLinearVelocity({ 0.7f,0.0f });
			}
			if (dragonPosition.x > intitialDragonPosition.x)
			{
				currentDragonAnimation = &rightDragon;
				dragonBody->body->SetLinearVelocity({ -0.7f,0.0f });

			}
			if (dragonPosition.y > intitialDragonPosition.y)
			{
				dragonBody->body->SetLinearVelocity({ 0.0f,-0.7f });
			}
			if (dragonPosition.y < intitialDragonPosition.y)
			{
				dragonBody->body->SetLinearVelocity({ 0.0f,0.7f });
			}
			if (dragonPosition.x < intitialDragonPosition.x && dragonPosition.y >  intitialDragonPosition.y)
			{
				currentDragonAnimation = &leftDragon;
				dragonBody->body->SetLinearVelocity({ 0.7f,-0.7f });

			}
			if (dragonPosition.x > intitialDragonPosition.x && dragonPosition.y > intitialDragonPosition.y)
			{
				currentDragonAnimation = &rightDragon;
				dragonBody->body->SetLinearVelocity({ -0.7f,-0.7f });

			}
			if (dragonPosition.x < intitialDragonPosition.x && dragonPosition.y < intitialDragonPosition.y)
			{
				currentDragonAnimation = &leftDragon;
				dragonBody->body->SetLinearVelocity({ 0.7f,0.7f });

			}
			if (dragonPosition.x > intitialDragonPosition.x && dragonPosition.y < intitialDragonPosition.y)
			{
				currentDragonAnimation = &rightDragon;
				dragonBody->body->SetLinearVelocity({ -0.7f,0.7f });

			}
		}
	}


	currentDragonAnimation->Update();

	return true;
}

// Called each loop iteration
bool EnemyDragon::PostUpdate()
{

	bool ret = true;

	//Bird
	SDL_Rect rectBird = currentDragonAnimation->GetCurrentFrame();
	dragonBody->GetPosition(dragonPosition.x, dragonPosition.y);
	app->render->DrawTexture(bird, dragonPosition.x, dragonPosition.y, &rectBird);

	return ret;
}

void EnemyDragon::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{

}

bool EnemyDragon::LoadState(pugi::xml_node& data)
{

	dragonPosition.x = data.child("dragonPosition").attribute("x").as_int();
	dragonPosition.y = data.child("dragonPosition").attribute("y").as_int();
	dragonBody->body->SetTransform({ PIXEL_TO_METERS(dragonPosition.x), PIXEL_TO_METERS(dragonPosition.y) }, 0.0f);

	return true;
}

bool EnemyDragon::SaveState(pugi::xml_node& data)
{

	data.child("dragonPosition").attribute("x").set_value(dragonPosition.x);
	data.child("dragonPosition").attribute("y").set_value(dragonPosition.y);

	return true;
}

bool EnemyDragon::CleanUp()
{
	LOG("Destroying Enemy");
	bool ret = true;
	app->tex->UnLoad(texture);
	//app->physics->world->DestroyBody(dragonBody->body);
	app->enemyDragon->destroyedDragon = true;
	app->tex->UnLoad(bird);
	return ret;
}
