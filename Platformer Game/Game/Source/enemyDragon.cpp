
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

EnemyDragon::EnemyDragon() : Module()
{
	name.Create("Enemy");

	//Dragon Animations

	//idleAnimRight
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
	leftDragon.speed = 0.4f;


	//leftAnim
	rightDragon.PushBack({ 167, 167, 29, 27 });
	rightDragon.PushBack({ 138, 168, 30, 27 });
	rightDragon.PushBack({ 111, 167, 28, 27 });
	rightDragon.PushBack({ 83, 167, 28, 28 });
	rightDragon.PushBack({ 55, 168, 28, 27 });
	rightDragon.PushBack({ 27, 167, 28, 28 });
	rightDragon.loop = true;
	rightDragon.speed = 0.4f;

	pathfinding = new PathFinding();
	name.Create("ground_enemy");

}

EnemyDragon::~EnemyDragon()
{

}

bool EnemyDragon::Awake(pugi::xml_node& config)
{

	positionDragon.x = config.child("position").attribute("x").as_int();
	positionDragon.y = config.child("position").attribute("y").as_int();

	return true;
}

bool EnemyDragon::Start()
{
	currentAnim = &idleLeftDragon;
	position = app->map->MapToWorld(14, 71.33);

	positionDragon.x = position.x;
	positionDragon.y = position.y;

	bool ret = true;

	texture = app->tex->Load("Assets/textures/DragonEnemy.png");

	b2BodyDef dragonBody1;
	dragonBody1.type = b2_dynamicBody;
	dragonBody1.position.Set(PIXEL_TO_METERS(positionDragon.x), PIXEL_TO_METERS(positionDragon.y));
	dragonBody1.fixedRotation = true;
	//create the body in  the world
	bDragon = app->physics->world->CreateBody(&dragonBody1);
	//add a shape
	DragonCircle.m_radius = PIXEL_TO_METERS(12);;
	//add fixture
	b2FixtureDef dragonFixture;
	dragonFixture.shape = &DragonCircle;
	dragonFixture.density = 1.5f;
	dragonFixture.friction = 100.0f;
	//add fixture to body
	bDragon->CreateFixture(&dragonFixture);
	// Create our custom PhysBody class
	dragonBody = new PhysBody();
	dragonBody->body = bDragon;
	dragonBody->width = dragonBody->height = DragonCircle.m_radius;
	dragonBody->listener = this;
	dragonBody->type = DRAGON;
	bDragon->SetUserData(dragonBody);

	int w, h;
	uchar* data = NULL;

	if (app->map->WalkablePath(w, h, &data)) pathfinding->SetMap(w, h, data);

	RELEASE_ARRAY(data);

	navigationPath = app->tex->Load("Assets/maps/navegationBox.png");

	return ret;
}

bool EnemyDragon::PreUpdate()
{
	aggro = CheckAggro();

	return true;
}
bool EnemyDragon::Update(float dt)
{

	enemyDragonPath();
	enemyDragonMove();


	return true;

	currentAnim->Update();

	dragonBody->GetPosition(DragonPosition.x, DragonPosition.y);
}

bool EnemyDragon::PostUpdate()
{


	SDL_Rect rect = currentAnim->GetCurrentFrame();
	app->render->DrawTexture(texture, positionDragon.x, positionDragon.y, &rect);

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

void EnemyDragon::enemyDragonPath()
{
	iPoint origin = { (int)METERS_TO_PIXELS((int)dragonBody->body->GetPosition().x), (int)METERS_TO_PIXELS((int)dragonBody->body->GetPosition().y) };
	iPoint destination = { (int)METERS_TO_PIXELS((int)app->player->pbody->body->GetPosition().x), (int)METERS_TO_PIXELS((int)app->player->pbody->body->GetPosition().y) };

	origin = app->map->WorldToMap(origin.x, origin.y);
	destination = app->map->WorldToMap(destination.x, destination.y);

	pathfinding->CreatePath(origin, destination);
	currentPath = pathfinding->GetLastPath();
}

void EnemyDragon::enemyDragonMove()
{
	//collider->SetPos(position.x, position.y);
	//Flying_Enemy_2_List.end->data->GetPosition(position.x, position.y);

	if (position.DistanceTo(app->player->position) < 200)
	{
		if (position.x < app->player->position.x)
		{
			if (currentAnimation != &leftDragon)
			{
				leftDragon.Reset();
				currentAnimation = &leftDragon;
			}
			dragonBody->body->SetLinearVelocity({ 0.7f,0.0f });

		}
		if (position.x > app->player->position.x)
		{
			if (currentAnimation != &rightDragon)
			{
				rightDragon.Reset();
				currentAnimation = &rightDragon;
			}
			currentAnim = &rightDragon;
			dragonBody->body->SetLinearVelocity({ -0.7f,0.0f });

		}

	}
	else
	{
		if (position.x < app->player->position.x)
		{
			if (currentAnimation != &idleLeftDragon)
			{
				idleLeftDragon.Reset();
				currentAnimation = &idleLeftDragon;
			}
			dragonBody->body->SetLinearVelocity({ 0.7f,0.0f });

		}
		if (position.x > app->player->position.x)
		{
			if (currentAnimation != &idleRightDragon)
			{
				idleRightDragon.Reset();
				currentAnimation = &idleRightDragon;
			}
			currentAnim = &rightDragon;
			dragonBody->body->SetLinearVelocity({ -0.7f,0.0f });

		}

	}

}

void EnemyDragon::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{

}

bool EnemyDragon::CheckAggro()
{
	uint dist = abs(sqrt(pow(dragonBody->body->GetPosition().x - app->player->pbody->body->GetPosition().x, 2) +
		pow(dragonBody->body->GetPosition().y - app->player->pbody->body->GetPosition().y, 2)));
	if (dist < aggroDistance) return true;
	if (dist > aggroDistance) return false;
}

bool EnemyDragon::LoadState(pugi::xml_node& node)
{
	return true;
}

bool EnemyDragon::SaveState(pugi::xml_node& node)
{
	return true;
}

bool EnemyDragon::CleanUp()
{
	return true;
}


