
#include "enemyBird.h"
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

EnemyBird::EnemyBird() : Module()
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

	pathfinding = new PathFinding();
	name.Create("flying_enemy");

}

EnemyBird::~EnemyBird()
{

}

bool EnemyBird::Awake(pugi::xml_node& config)
{

	birdPosition.x = config.child("position").attribute("x").as_int();
	birdPosition.y = config.child("position").attribute("y").as_int();

	return true;
}

bool EnemyBird::Start()
{
	currentAnim = &idleLeftBird;
	position = app->map->MapToWorld(10, 69);

	birdPosition.x = position.x;
	birdPosition.y = position.y;

	bool ret = true;

	texture = app->tex->Load("Assets/textures/enemyBird.png");

	b2BodyDef birdBody1;
	birdBody1.type = b2_dynamicBody;
	birdBody1.position.Set(PIXEL_TO_METERS(birdPosition.x), PIXEL_TO_METERS(birdPosition.y));
	birdBody1.fixedRotation = true;
	//create the body in  the world
	bBird = app->physics->world->CreateBody(&birdBody1);
	//add a shape
	birdCircle.m_radius = PIXEL_TO_METERS(12);;
	//add fixture
	b2FixtureDef birdFixture;
	birdFixture.shape = &birdCircle;
	birdFixture.density = 1.5f;
	birdFixture.friction = 100.0f;
	//add fixture to body
	bBird->CreateFixture(&birdFixture);
	// Create our custom PhysBody class
	birdBody = new PhysBody();
	birdBody->body = bBird;
	birdBody->width = birdBody->height = birdCircle.m_radius;
	birdBody->listener = this;
	birdBody->type = BIRD;
	bBird->SetUserData(birdBody);

	int w, h;
	uchar* data = NULL;

	if (app->map->WalkablePath(w, h, &data)) pathfinding->SetMap(w, h, data);

	RELEASE_ARRAY(data);

	navigationPath = app->tex->Load("Assets/maps/navegationBox.png");

	return ret;
}

bool EnemyBird::PreUpdate()
{
	aggro = CheckAggro();

	return true;
}
bool EnemyBird::Update(float dt)
{
	
	enemyBirdPath();
	enemyBirdMove();

	
	return true;

	currentAnim->Update();

	birdBody->GetPosition(birdPosition.x, birdPosition.y);
}

bool EnemyBird::PostUpdate()
{
	
	
	SDL_Rect rect = currentAnim->GetCurrentFrame();
	app->render->DrawTexture(texture, birdPosition.x, birdPosition.y, &rect);

	if (aggro && app->physics->debug)
	{
		for (uint i = 0; i < currentPath->Count(); ++i)
		{
			iPoint pos = app->map->MapToWorld(currentPath->At(i)->x, currentPath->At(i)->y);
			app->render->DrawTexture(navigationPath, pos.x, pos.y);
		}
	}

	return true;
}

void EnemyBird::enemyBirdPath()
{
	iPoint origin = { (int)METERS_TO_PIXELS((int)birdBody->body->GetPosition().x), (int)METERS_TO_PIXELS((int)birdBody->body->GetPosition().y) };
	iPoint destination = { (int)METERS_TO_PIXELS((int)app->player->pbody->body->GetPosition().x), (int)METERS_TO_PIXELS((int)app->player->pbody->body->GetPosition().y) };

	origin = app->map->WorldToMap(origin.x, origin.y);
	destination = app->map->WorldToMap(destination.x, destination.y);

	pathfinding->CreatePath(origin, destination);
	currentPath = pathfinding->GetLastPath();
}

void EnemyBird::enemyBirdMove()
{
	//collider->SetPos(position.x, position.y);
	//Flying_Enemy_2_List.end->data->GetPosition(position.x, position.y);

	if (position.DistanceTo(app->player->position) < 200)
	{
		if (position.x < app->player->position.x)
		{
			currentAnim = &leftBird;
			birdBody->body->SetLinearVelocity({ 0.7f,0.0f });

		}
		if (position.x > app->player->position.x)
		{
			currentAnim = &rightBird;
			birdBody->body->SetLinearVelocity({ -0.7f,0.0f });

		}
		if (position.y > app->player->position.y)
		{
			birdBody->body->SetLinearVelocity({ 0.0f,-0.5f });
		}
		if (position.y < app->player->position.y)
		{
			birdBody->body->SetLinearVelocity({ 0.0f,0.5f });
		}
		if (position.x < app->player->position.x && position.y > app->player->position.y)
		{
			currentAnim = &leftBird;
			birdBody->body->SetLinearVelocity({ 0.7f,-0.5f });

		}
		if (position.x > app->player->position.x && position.y > app->player->position.y)
		{
			currentAnim = &rightBird;
			birdBody->body->SetLinearVelocity({ -0.7f,-0.5f });

		}
		if (position.x < app->player->position.x && position.y < app->player->position.y)
		{
			currentAnim = &leftBird;
			birdBody->body->SetLinearVelocity({ 0.7f,0.5f });

		}
		if (position.x > app->player->position.x && position.y < app->player->position.y)
		{
			currentAnim = &rightBird;
			birdBody->body->SetLinearVelocity({ -0.7f,0.5f });

		}
	}

}

void EnemyBird::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{

}

bool EnemyBird::CheckAggro()
{
	uint dist = abs(sqrt(pow(birdBody->body->GetPosition().x - app->player->pbody->body->GetPosition().x, 2) +
		pow(birdBody->body->GetPosition().y - app->player->pbody->body->GetPosition().y, 2)));
	if (dist < aggroDistance) return true;
	if (dist > aggroDistance) return false;
}

bool EnemyBird::LoadState(pugi::xml_node& node)
{
	return true;
}

bool EnemyBird::SaveState(pugi::xml_node& node)
{
	return true;
}

bool EnemyBird::CleanUp()
{
	return true;
}


