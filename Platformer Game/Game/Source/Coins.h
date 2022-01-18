#include "Module.h"
#include "List.h"
#include "Animation.h"
#include "App.h"
#include "Point.h"
#include "ModulePhysics.h"
#include "SString.h"


struct SDL_Texture;

class Coins : public Module
{
public:
	Coins();
	~Coins();

	bool Awake(pugi::xml_node&);
	bool Start();

	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);


	iPoint coinPosition;
	iPoint flagPosition;
	typeOfCollision typeCoin;
	PhysBody* coinBody;
	PhysBody* checkPointBody;
	b2Body* c;

	b2CircleShape pCircle;

	Animation* currentCoinAnimation = nullptr;
	Animation anim;
	Animation animFlag;
	Animation* currentFlagAnimation = nullptr;

	bool pendingToDelete = false;

	bool destroyed = false;
	bool coinCollected = false;

	SDL_Texture* texture = nullptr;

private:
	SString folder;
	SDL_Texture* coin;
	SDL_Texture* checkpointFlag;
};
#pragma once
