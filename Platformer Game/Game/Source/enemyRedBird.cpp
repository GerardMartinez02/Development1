
#include "enemyRedBird.h"
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

EnemyRedBird::EnemyRedBird()
{
	name.Create("Enemy");

	//Bird Animations

	//idleAnimRight
	idleRightBird.PushBack({ 0, 35, 40, 40 });

	//idleAnimLeft
	idleLeftBird.PushBack({ 115, 114, 40, 40 });

	//rightAnim
	leftBird.PushBack({ 0, 3, 31, 34 });
	leftBird.PushBack({ 32, 3, 31, 32 });
	leftBird.PushBack({ 64, 3, 38, 38 });
	leftBird.PushBack({ 102, 3, 38, 38 });
	leftBird.loop = true;
	leftBird.speed = 0.1f;


	//leftAnim
	rightBird.PushBack({ 18, 77, 36, 31 });
	rightBird.PushBack({ 54, 77, 36, 31 });
	rightBird.PushBack({ 92, 80, 31, 31 });
	rightBird.PushBack({ 124, 81, 31, 31 });
	rightBird.loop = true;
	rightBird.speed = 0.1f;

}
EnemyRedBird::~EnemyRedBird()
{

}

bool EnemyRedBird::Awake(pugi::xml_node& config)
{
	LOG("Loading Enemy");
	bool ret = true;
	//textureBird.Create(config.child("textureBird").child_value());

	//startPosBird.x = config.child("startPositionBird").attribute("x").as_int();
	//startPosBird.y = config.child("startPositionBird").attribute("y").as_int();

	// Enemy's speed
	speed = config.child("speed").attribute("value").as_int();
	return ret;
}

// Called before the first frame
bool EnemyRedBird::Start()
{
	destroyedBird = false;
	// Load enemies

	bird = app->tex->Load("Assets/textures/enemies/enemyRedBird.png");

	// stating animation

	currentBirdAnimation = &idleLeftBird;

	startPosBird = app->map->MapToWorld(161, 69);

	//startPosBird.x = 5;
	//startPosBird.y = 69;

	birdPosition.x = startPosBird.x;
	birdPosition.y = startPosBird.y;

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


	birdBody = app->physics->CreateEnemyBird(birdPosition.x, birdPosition.y, Hitbox, 16, 0);
	birdBody->listener = this;
	birdBody->type = REDBIRD;
	birdDead = false;

	return true;
}

// Called each loop iteration
bool EnemyRedBird::PreUpdate()
{
	/*OPTICK_CATEGORY("lvl1 PreUpdate", Optick::Category::Scene);*/
	return true;
}

// Called each loop iteration
bool EnemyRedBird::Update(float dt)
{
	if (app->player->pauseMenu == true)
	{
		iPoint NewPosition = birdPosition;
		birdBody->GetPosition(NewPosition.x, NewPosition.y);
		if (birdPosition.x < app->player->position.x) currentBirdAnimation = &leftBird;
		if (birdPosition.x > app->player->position.x) currentBirdAnimation = &rightBird;
		currentBirdAnimation->loop = false;

		birdBody->body->SetLinearVelocity({ 0.0f,0.0f });
	}
	if (birdDead == false && app->player->pauseMenu == false)
	{

		BirdVelocity = birdBody->body->GetLinearVelocity();

		birdBody->body->SetLinearVelocity(BirdVelocity);

		if (birdPosition.DistanceTo(app->player->position) < 400)
		{
			if (birdPosition.x < app->player->position.x)
			{
				currentBirdAnimation = &leftBird;
				birdBody->body->SetLinearVelocity({ 0.85f,0.0f });

			}
			if (birdPosition.x > app->player->position.x)
			{
				currentBirdAnimation = &rightBird;
				birdBody->body->SetLinearVelocity({ -0.85f,0.0f });

			}
			if (birdPosition.y > app->player->position.y)
			{
				birdBody->body->SetLinearVelocity({ 0.0f,-0.6f });
			}
			if (birdPosition.y < app->player->position.y)
			{
				birdBody->body->SetLinearVelocity({ 0.0f,0.6f });
			}
			if (birdPosition.x < app->player->position.x && birdPosition.y > app->player->position.y)
			{
				currentBirdAnimation = &leftBird;
				birdBody->body->SetLinearVelocity({ 0.85f,-0.6f });

			}
			if (birdPosition.x > app->player->position.x && birdPosition.y > app->player->position.y)
			{
				currentBirdAnimation = &rightBird;
				birdBody->body->SetLinearVelocity({ -0.85f,-0.6f });

			}
			if (birdPosition.x < app->player->position.x && birdPosition.y < app->player->position.y)
			{
				currentBirdAnimation = &leftBird;
				birdBody->body->SetLinearVelocity({ 0.85f,0.6f });

			}
			if (birdPosition.x > app->player->position.x && birdPosition.y < app->player->position.y)
			{
				currentBirdAnimation = &rightBird;
				birdBody->body->SetLinearVelocity({ -0.85f,0.6f });

			}
		}
		else
		{
			if (birdPosition.x == startPosBird.x && birdPosition.y == startPosBird.y)
			{
				if (currentBirdAnimation == &leftBird)
				{
					currentBirdAnimation = &idleRightBird;
					birdBody->body->SetLinearVelocity({ 0.0f,0.0f });
				}
				if (currentBirdAnimation == &rightBird)
				{
					currentBirdAnimation = &idleLeftBird;
					birdBody->body->SetLinearVelocity({ 0.0f,0.0f });
				}
			}
			if (birdPosition.x < startPosBird.x)
			{
				currentBirdAnimation = &leftBird;
				birdBody->body->SetLinearVelocity({ 0.85f,0.0f });
			}
			if (birdPosition.x > startPosBird.x)
			{
				currentBirdAnimation = &rightBird;
				birdBody->body->SetLinearVelocity({ -0.85f,0.0f });

			}
			if (birdPosition.y > startPosBird.y)
			{
				birdBody->body->SetLinearVelocity({ 0.0f,-0.6f });
			}
			if (birdPosition.y < startPosBird.y)
			{
				birdBody->body->SetLinearVelocity({ 0.0f,0.6f });
			}
			if (birdPosition.x < startPosBird.x && birdPosition.y >  startPosBird.y)
			{
				currentBirdAnimation = &leftBird;
				birdBody->body->SetLinearVelocity({ 0.85f,-0.6f });

			}
			if (birdPosition.x > startPosBird.x && birdPosition.y > startPosBird.y)
			{
				currentBirdAnimation = &rightBird;
				birdBody->body->SetLinearVelocity({ -0.85f,-0.6f });

			}
			if (birdPosition.x < startPosBird.x && birdPosition.y < startPosBird.y)
			{
				currentBirdAnimation = &leftBird;
				birdBody->body->SetLinearVelocity({ 0.85f,0.6f });

			}
			if (birdPosition.x > startPosBird.x && birdPosition.y < startPosBird.y)
			{
				currentBirdAnimation = &rightBird;
				birdBody->body->SetLinearVelocity({ -0.85f,0.6f });

			}
		}
	}


	currentBirdAnimation->Update();

	return true;
}

// Called each loop iteration
bool EnemyRedBird::PostUpdate()
{

	bool ret = true;

	//Bird
	SDL_Rect rectBird = currentBirdAnimation->GetCurrentFrame();
	birdBody->GetPosition(birdPosition.x, birdPosition.y);
	app->render->DrawTexture(bird, birdPosition.x, birdPosition.y, &rectBird);

	return ret;
}

void EnemyRedBird::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{

}

bool EnemyRedBird::LoadState(pugi::xml_node& data)
{

	birdPosition.x = data.child("birdPosition").attribute("x").as_int();
	birdPosition.y = data.child("birdPosition").attribute("y").as_int();
	birdBody->body->SetTransform({ PIXEL_TO_METERS(birdPosition.x), PIXEL_TO_METERS(birdPosition.y) }, 0.0f);

	return true;
}

bool EnemyRedBird::SaveState(pugi::xml_node& data)
{

	data.child("birdPosition").attribute("x").set_value(birdPosition.x);
	data.child("birdPosition").attribute("y").set_value(birdPosition.y);

	return true;
}

bool EnemyRedBird::CleanUp()
{
	LOG("Destroying Enemy");
	bool ret = true;
	app->tex->UnLoad(texture);
	//app->physics->world->DestroyBody(birdBody->body);
	app->enemyRedBird->destroyedBird = true;
	app->tex->UnLoad(bird);
	return ret;
}

