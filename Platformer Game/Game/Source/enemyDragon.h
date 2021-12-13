#ifndef __ENEMYDRAGON_H__
#define __ENEMYDRAGON_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"
#include "Box2D/Box2D/Box2D.h"
#include "List.h"
#include "Map.h"
#include "ModulePhysics.h"
#include "App.h"

struct SDL_Texture;
struct Collider;

class EnemyDragon : public Module, public b2ContactListener
{
public:
	iPoint position;
	// Constructor
	EnemyDragon();

	EnemyDragon(int x, int y);

	// Destructor
	~EnemyDragon();

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

	// Called before quitting
	bool CleanUp();

	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&);
	void DragonDies();

private:
	PathFinding* pathfinding;
	b2Fixture* enemySensor;

	SDL_Texture* Dragon;
	SString textureDragon;
	SDL_Rect enemyRec;
	SDL_Texture* navigationPath;

	Animation* currentAnimation = nullptr;

	Animation idleLeftDragon;
	Animation idleRightDragon;
	Animation leftDragon;
	Animation rightDragon;
	Animation* currentDragonAnim = nullptr;
	b2Vec2 DragonVelocity;

	bool DragonBoundsRight = false;
	bool DragonBoundsLeft = true;

	void enemyDragonMove();
	void enemyDragonPath();
	bool CheckAggro();
	bool aggro;
	int aggroDistance = 8;
	bool setToDestroy = false;
	bool isAlive = true;
	b2Vec2 speed = { 2.0f, -2.0f };

public:

	// The current position in the world
	iPoint DragonPosition;

	// The enemy's texture
	SDL_Texture* texture = nullptr;

	// Sound fx when destroyed
	int destroyedFx = 0;

	// A flag for the enemy removal. Important! We do not delete objects instantly
	bool pendingToDelete = false;

	iPoint positionDragon;
	iPoint startPosDragond;

	b2Vec2* velocity;

	PhysBody* dragonBody;
	b2Body* bDragon;
	b2CircleShape DragonCircle;
	const DynArray<iPoint>* currentPath;
	// The speed in which we move the player (pixels per frame)

	typeOfCollision* type;

protected:
	// A ptr to the current animation
	Animation* currentAnim = nullptr;

	// The enemy's collider
	Collider* collider = nullptr;

	// Original spawn position. Stored for movement calculations
	iPoint spawnPos;
};

#endif;

