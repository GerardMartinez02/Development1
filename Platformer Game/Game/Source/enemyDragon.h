#ifndef __ENEMYDRAGON_H__
#define __ENEMYDRAGON_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"
#include "Box2D/Box2D/Box2D.h"
#include "List.h"
#include "ModulePhysics.h"

struct SDL_Texture;
struct Collider;

class EnemyDragon : public Module
{
public:
	// Constructor
	// Saves the spawn position for later movement calculations
	EnemyDragon();

	// Destructor
	~EnemyDragon();

	// Collision response
	// Triggers an animation and a sound fx
	// Collision callback, called when the player intersects with another collider
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB) override;


	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Save and load the position of the enemies
	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&);

	// Called before quitting
	bool CleanUp();

private:

	SDL_Texture* bird;

	SString textureDragon;


	Animation leftDragon;
	Animation rightDragon;
	Animation idleRightDragon;
	Animation idleLeftDragon;

	Animation* currentDragonAnimation = nullptr;

	b2Vec2 dragonVelocity;
public:

	// The current position in the world

	iPoint dragonPosition;

	// The enemy's texture
	SDL_Texture* texture = nullptr;

	// Sound fx when destroyed
	int destroyedFx = 0;

	// A flag for the enemy removal. Important! We do not delete objects instantly
	bool pendingToDelete = false;

	bool dragonDead = false;

	/*iPoint direction = { 0, 0 };*/
	// Position of the player in the map

	iPoint intitialDragonPosition;

	b2Vec2* velocity;

	// player's body

	PhysBody* dragonBody;
	b2Body* bDragon;

	//add a shape
	b2CircleShape dragonCircle;

	// The speed in which we move the player (pixels per frame)
	int speed;

	bool destroyedDragon;

	bool onGround;
};

#endif // __ENEMY_H__